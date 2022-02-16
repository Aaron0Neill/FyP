#include <shapeManager.h>

ShapeManager::ShapeManager()
{
	m_world = WorldManager::getInstance()->getWorld();
}

//*************************************************************

PolyID ShapeManager::createPolygon(uint8 t_sides, float t_radius, Vector t_pos)
{
	assert(t_sides >= 3 && t_sides <= 8);
	PolyID currentID = m_polygonIndex ++;
	PolygonShape newShape;
	newShape.m_vertex.resize(t_sides + 1);
	auto points = PolygonShape::getPoints(t_sides, t_radius);

	b2PolygonShape s;
	s.Set(points, t_sides);
	
	b2BodyDef def = generateBodyDef(t_pos.toWorldSpace());
	newShape.m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.0f;
	newShape.m_fixture = newShape.m_body->CreateFixture(&fixtureDef);

	m_polygons.push_back(newShape);

	delete points;

	return currentID;
}

//*************************************************************

CircleID ShapeManager::createCircle(float t_radius, Vector t_position)
{
	CircleID currentID = m_circleIndex++;
	CircleShape newShape(t_radius * PixelsPerMetre);

	b2CircleShape s;
	s.m_radius = t_radius;

	b2BodyDef def = generateBodyDef(t_position.toWorldSpace());
	newShape.m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
	fixtureDef.density = 1.0f;
	newShape.m_fixture = newShape.m_body->CreateFixture(&fixtureDef);

	m_circles.push_back(newShape);

	return currentID;
}

//*************************************************************

PolyID ShapeManager::createEdge(Vector t_p1, Vector t_p2)
{
	PolyID currentID = m_polygonIndex++;
	PolygonShape newShape;
	newShape.m_vertex.resize(2);
	newShape.m_vertex[0].position = t_p1;
	newShape.m_vertex[1].position = t_p2;

	b2EdgeShape s;
	s.SetTwoSided(t_p1.toWorldSpace(), t_p2.toWorldSpace());

	b2BodyDef def;
	newShape.m_body = m_world->CreateBody(&def);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &s;
 	fixtureDef.density = 1.0f;
	newShape.m_fixture = newShape.m_body->CreateFixture(&fixtureDef);

	m_polygons.push_back(newShape);

	return currentID;
}

//*************************************************************

void ShapeManager::update()
{
	for (PolygonShape& p : m_polygons)
		p.update();

	for (CircleShape& c : m_circles)
		c.update();
}

//*************************************************************

void ShapeManager::draw(sf::RenderWindow* t_window)
{
	for (PolygonShape& p : m_polygons)
		t_window->draw(p.m_vertex);

	for (CircleShape& c : m_circles)
		c.draw(t_window);
}

//*************************************************************

b2Joint* ShapeManager::createDistanceJoint(PolyID t_polyid, CircleID t_circID, float t_distance)
{
	b2DistanceJointDef jointDef;
	jointDef.bodyA = m_polygons[t_polyid].getBody();
	jointDef.bodyB = m_circles[t_circID].getBody();
	jointDef.maxLength = t_distance;

	WorldManager::getInstance()->getWorld()->CreateJoint(&jointDef);

	b2Joint* j = m_world->CreateJoint(&jointDef);
	return j;
}

//*************************************************************

void ShapeManager::startWorld()
{
	for (auto s : m_circles)
		s.getBody()->SetAwake(true);

	for (auto p : m_polygons)
		p.getBody()->SetAwake(true);
}

//*************************************************************

b2BodyDef ShapeManager::generateBodyDef(Vector t_pos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = t_pos;
	return bodyDef;
}
