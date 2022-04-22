#include <shapeManager.h>

ShapeManager::ShapeManager()
{
}

//*************************************************************

ShapeManager::~ShapeManager()
{
	reset();
}

//*************************************************************

ShapeManager* ShapeManager::getInstance()
{
	static ShapeManager instance;
	return &instance;	
}

//*************************************************************

void ShapeManager::setWorld(b2World* t_world)
{
	m_world = t_world;
	ContactListener* listener = new ContactListener();
	m_world->SetContactListener(listener);
}

//*************************************************************

ShapeID ShapeManager::createPolygon(uint8 t_sides, float t_radius, Vector t_pos)
{
	assert(t_sides >= 3 && t_sides <= 8);
	ShapeID currentID = m_shapes.size();
	PolygonShape* newShape = new PolygonShape();
	newShape->m_vertex.resize(t_sides + 1);

	for (uint8 i = 0; i < t_sides + 1; ++i)
		newShape->m_vertex[i].color = { 40U,40U,40U,255U };

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
	ShapeID currentID = m_shapes.size();
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
	ShapeID currentID = m_shapes.size();
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

ShapeID ShapeManager::createSprite(Texture t_texture, Vector t_centre)
{
	Vector size = static_cast<sf::Vector2f>(t_texture->getSize());
	Vector boxSize = size.toWorldSpace() / 2.f;

	size_t vertCount = 4U;

	PolygonShape* newShape = new PolygonShape();
	newShape->m_vertex.resize(vertCount);
	newShape->m_state.texture = t_texture.get();

	newShape->m_vertex[0].texCoords = { 0		, 0};
	newShape->m_vertex[1].texCoords = { size.x	, 0 };
	newShape->m_vertex[2].texCoords = { size.x	, size.y};
	newShape->m_vertex[3].texCoords = { 0		, size.y};

	for (size_t i = 0; i < vertCount; ++i)
		newShape->m_vertex[i].color = sf::Color::White;

	b2PolygonShape s;
	s.SetAsBox(boxSize.x, boxSize.y);

	b2BodyDef def = generateBodyDef(t_centre.toWorldSpace());
	newShape->m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.f;
	newShape->m_fixture = newShape->m_body->CreateFixture(&fixtureDef);

	m_shapes.push_back(newShape);
	return ShapeID(m_shapes.size() - 1);
}

ShapeID ShapeManager::createSprite(std::string t_textureName, Vector t_centre)
{
	TextureManager* tm = TextureManager::getInstance();
	Texture tex = tm->getTexture(t_textureName);
	return createSprite(tex, t_centre);
}

//*************************************************************

void ShapeManager::update()
{
	for (auto iter = m_shapes.begin(); iter != m_shapes.end(); ++iter)
	{
		if ((*iter)->m_destroy)
			iter = destroyShape(*iter);
		if (iter == m_shapes.end())
			break;
	}

	for (auto& shape : m_shapes)
	{
		shape->update();
	}

#ifdef BUILD_SRC
	size_t jointCount = m_joints.size();
	if (m_jointsArray.getVertexCount() < m_joints.size() * 2)
		m_jointsArray.resize(jointCount * 2U);

	for (size_t i = 0; i < jointCount; ++i)
	{
		size_t vertIndex = i * 2;
		m_jointsArray[vertIndex].position = Vector(m_joints[i]->GetAnchorA()).fromWorldSpace();
		m_jointsArray[vertIndex+1].position = Vector(m_joints[i]->GetAnchorB()).fromWorldSpace();
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
		if (IShape* shape = *it)
			if (shape->getBody() == t_shape)
				return it - m_shapes.begin();

	return ShapeID(255);
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

void ShapeManager::destroy(ShapeID t_id)
{
	if (t_id < m_shapes.size())
	{
		auto iter = m_shapes.begin() + t_id;
		std::cout << "id: " << (int)t_id << std::endl;
		m_world->DestroyBody((*iter)->getBody());
		m_shapes.erase(iter);
	}
}

//*************************************************************

void ShapeManager::destroy(IShape* t_shape)
{
	t_shape->m_destroy = true;
}

//*************************************************************

void ShapeManager::destroy(b2Body* t_body)
{
	auto iter = std::find_if(m_shapes.begin(), m_shapes.end(), [t_body](IShape* t_current) { return t_current->getBody() == t_body; });
	destroy(*iter);
}

void ShapeManager::destroy(const IShape& t_other)
{
	t_other.m_destroy = true;
}

//*************************************************************

void ShapeManager::reset()
{
	for (IShape* shape : m_shapes)
	{
		m_world->DestroyBody(shape->getBody());
		delete shape;
	}
	m_shapes.clear();

	for (b2Joint* joint : m_joints)
		m_world->DestroyJoint(joint);

	m_joints.clear();
}

//*************************************************************

b2BodyDef ShapeManager::generateBodyDef(Vector t_pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = t_pos;
	return bodyDef;
}

//*************************************************************

std::vector<IShape*>::iterator ShapeManager::destroyShape(IShape* t_shape)
{
	auto iter = std::find_if(m_shapes.begin(), m_shapes.end(), [t_shape](IShape* t_current) { return t_current == t_shape; });
	m_world->DestroyBody((*iter)->getBody());
	delete* iter;
	return m_shapes.erase(iter);
}
