#include <shapeManager.h>

ShapeManager::ShapeManager()
{
	m_world = WorldManager::getInstance()->getWorld();
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

	size_t jointCount = m_joints.size();
	if (m_jointsArray.getVertexCount() < m_joints.size() * 2)
		m_jointsArray.resize(jointCount * 2U);

	for (size_t i = 0; i < jointCount; ++i)
	{
		size_t vertIndex = i * 2;
		m_jointsArray[vertIndex].position = Vector(m_joints[i]->GetBodyA()->GetPosition()).fromWorldSpace();
		m_jointsArray[vertIndex+1].position = Vector(m_joints[i]->GetBodyB()->GetPosition()).fromWorldSpace();
	}
}

//*************************************************************

void ShapeManager::draw(sf::RenderWindow* t_window)
{
	for (auto& shape : m_shapes)
		shape->draw(t_window);

	t_window->draw(m_jointsArray);
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

	WorldManager::getInstance()->getWorld()->CreateJoint(&jointDef);

	m_joints.push_back(m_world->CreateJoint(&jointDef));
	size_t size = m_joints.size();
	return m_joints[size-1];
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
