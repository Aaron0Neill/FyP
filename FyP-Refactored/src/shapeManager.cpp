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
	
	b2BodyDef def = generateBodyDef(t_pos.toWorldSpace());
	newShape->m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.0f;
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
 	fixtureDef.density = 1.0f;
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
}

//*************************************************************

void ShapeManager::draw(sf::RenderWindow* t_window)
{
	for (auto& shape : m_shapes)
		shape->draw(t_window);
}

//*************************************************************

b2Joint* ShapeManager::createDistanceJoint(ShapeID t_polyid, ShapeID t_circID, float t_distance)
{
	b2DistanceJointDef jointDef;
	jointDef.bodyA = m_shapes[t_polyid]->getBody();
	jointDef.bodyB = m_shapes[t_circID]->getBody();
	jointDef.maxLength = t_distance;

	WorldManager::getInstance()->getWorld()->CreateJoint(&jointDef);

	b2Joint* j = m_world->CreateJoint(&jointDef);
	return j;
}

//*************************************************************

void ShapeManager::startWorld()
{
	for (auto& shape : m_shapes)
		shape->getBody()->SetAwake(true);
}

//*************************************************************

b2BodyDef ShapeManager::generateBodyDef(Vector t_pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = t_pos;
	return bodyDef;
}
