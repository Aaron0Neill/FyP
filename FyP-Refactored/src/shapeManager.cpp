#include <shapeManager.h>

ShapeManager::ShapeManager(b2World* t_world) : 
	m_world(t_world)
{
	ContactListener* listener = new ContactListener(this);
	m_world->SetContactListener(listener);
}

//*************************************************************

ShapeManager::~ShapeManager()
{
	for (auto& shape : m_shapes)
		delete shape;
}

//*************************************************************

ShapeID ShapeManager::createPolygon(uint8 t_sides, float t_radius, Vector t_pos)
{
	assert(t_sides >= 3 && t_sides <= 8);
	ShapeID currentID = m_currentID++;
	PolygonShape* newShape = new PolygonShape();
	newShape->m_vertex.resize(t_sides + 1);
	auto points = PolygonShape::getPoints(t_sides, t_radius);

	b2PolygonShape s;
	s.Set(points, t_sides);

	if (t_sides == 4)
		s.SetAsBox(t_radius / 1.5f, t_radius / 1.5f);
	
	b2BodyDef def = generateBodyDef(t_pos.toWorldSpace());
	newShape->m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.f;
	newShape->m_fixture = newShape->m_body->CreateFixture(&fixtureDef);

	m_shapes.push_back(newShape);

	delete points;

	return currentID;
}

//*************************************************************

ShapeID ShapeManager::createCircle(float t_radius, Vector t_position)
{
	ShapeID currentID = m_currentID++;
	CircleShape* newShape = new CircleShape(t_radius * PixelsPerMetre);

	b2CircleShape s;
	s.m_radius = t_radius;

	b2BodyDef def = generateBodyDef(t_position.toWorldSpace());
	newShape->m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.0f;
	newShape->m_fixture = newShape->m_body->CreateFixture(&fixtureDef);

	m_shapes.push_back(newShape);

	return currentID;
}

//*************************************************************

ShapeID ShapeManager::createEdge(Vector t_p1, Vector t_p2)
{
	ShapeID currentID = m_currentID++;
	PolygonShape* newShape = new PolygonShape();
	newShape->m_vertex.resize(2);
	newShape->m_vertex.setPrimitiveType(sf::Lines);
	newShape->m_vertex[0].position = t_p1;
	newShape->m_vertex[1].position = t_p2;

	newShape->m_vertex[0].color = sf::Color::Black;
	newShape->m_vertex[1].color = sf::Color::Black;

	b2EdgeShape s;
	s.SetTwoSided(t_p1.toWorldSpace(), t_p2.toWorldSpace());

	b2BodyDef def;
	newShape->m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	newShape->m_fixture = newShape->m_body->CreateFixture(&fixtureDef);

	m_shapes.push_back(newShape);

	return currentID;
}

//*************************************************************

IShape* ShapeManager::isMouseOnShape(Vector t_mousePos)
{
	for (auto& shape : m_shapes)
		if (shape->getFixture()->TestPoint(t_mousePos.toWorldSpace()))
			return shape;
	return nullptr;
}

//*************************************************************

void ShapeManager::update()
{
	for (auto& shape : m_shapes)
		shape->update();

#ifdef BUILD_SRC
	size_t jointCount = m_joints.size();
	if (m_jointsArray.getVertexCount() < m_joints.size() * 2)
		m_jointsArray.resize(jointCount * 2U);

	for (size_t i = 0; i < jointCount; ++i)
	{
		size_t vertIndex = i * 2;
		m_jointsArray[vertIndex].position = Vector(m_joints[i]->GetBodyA()->GetPosition()).fromWorldSpace();
		m_jointsArray[vertIndex+1].position = Vector(m_joints[i]->GetBodyB()->GetPosition()).fromWorldSpace();
	}
#endif
}

//*************************************************************

IShape* ShapeManager::find(const std::string& t_name)
{
	for (auto& shape : m_shapes)
		if (shape->m_name == t_name)
			return shape;

	return nullptr;
}

//*************************************************************

void ShapeManager::draw(sf::RenderWindow* t_window)
{
	for (auto& shape : m_shapes)
		shape->draw(t_window);

#ifdef BUILD_SRC
	t_window->draw(m_jointsArray);
#endif
}

//*************************************************************

ShapeID ShapeManager::getID(IShape* t_shape)
{
	auto it = std::find(m_shapes.begin(), m_shapes.end(), t_shape);
	return it - m_shapes.begin();
}

//*************************************************************

ShapeID ShapeManager::getID(b2Body* t_shape)
{
	auto end = m_shapes.end();

	for (auto it = m_shapes.begin(); it != end; ++it)
		if ((*it)->getBody() == t_shape)
			return it - m_shapes.begin();

	return ShapeID(-1);
}

//*************************************************************

b2Joint* ShapeManager::createDistanceJoint(ShapeID t_shapeA, ShapeID t_shapeB)
{
	IShape* bodyA = m_shapes[t_shapeA];
	IShape* bodyB = m_shapes[t_shapeB];
	return createDistanceJoint(bodyA, bodyB);
}

//*************************************************************

b2Joint* ShapeManager::createDistanceJoint(IShape* t_bodyA, IShape* t_bodyB)
{
	b2DistanceJointDef jointDef;
	auto bodyA = t_bodyA->getBody();
	auto bodyB = t_bodyB->getBody();

	jointDef.Initialize(bodyA, bodyB, bodyA->GetPosition(), bodyB->GetPosition());

	jointDef.minLength = jointDef.length / 2.f;
	jointDef.maxLength = jointDef.length * 2.f;

	size_t size = m_joints.size();
	m_joints.push_back(m_world->CreateJoint(&jointDef));
	std::cout << m_joints.size() << std::endl;
	return m_joints[size];
}

//*************************************************************

b2Joint* ShapeManager::createWheelJoint(ShapeID t_bodyA, ShapeID t_bodyB)
{
	IShape* bodyA = m_shapes[t_bodyA];
	IShape* bodyB = m_shapes[t_bodyB];
	return createWheelJoint(bodyA, bodyB);
}

//*************************************************************

b2Joint* ShapeManager::createWheelJoint(IShape* t_bodyA, IShape* t_bodyB)
{
	b2WheelJointDef wheelJoint;
	b2Body* bodyA = t_bodyA->getBody();
	b2Body* bodyB = t_bodyB->getBody();

	wheelJoint.Initialize(bodyA, bodyB, bodyB->GetPosition(), { 0,1 });

	wheelJoint.enableLimit = true;
	wheelJoint.lowerTranslation = -0.5f;
	wheelJoint.upperTranslation = 0.5f;

	size_t size = m_joints.size();
	m_joints.push_back(m_world->CreateJoint(&wheelJoint));

	std::cout << m_joints.size() << std::endl;
	return m_joints[size];
}

//*************************************************************

void ShapeManager::startWorld()
{
	for (auto& shape : m_shapes)
		shape->getBody()->SetAwake(true);
}

//*************************************************************

void ShapeManager::saveShapes(jsonf& t_data)
{
	ShapeID id = 0;
	for (auto& shape : m_shapes)
	{
		if (shape == *m_shapes.begin())continue;

		jsonf& data = t_data[id++];
		shape->toJson(data);
	}
}

//*************************************************************

void ShapeManager::saveJoints(jsonf& t_data)
{
	ShapeID id = 0;

	for (auto& j : m_joints)
	{
		jsonf& data = t_data[id++];
		int jointType = j->GetType();
		data["Bodies"] = { getID(j->GetBodyA()), getID(j->GetBodyB()) };
	}
}

//*************************************************************

b2BodyDef ShapeManager::generateBodyDef(Vector t_pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = t_pos;
	return bodyDef;
}
