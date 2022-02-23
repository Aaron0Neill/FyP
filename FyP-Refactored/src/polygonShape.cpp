#include <polygonShape.h>

void PolygonShape::setScale(float t_newScale)
{
	if (t_newScale != 0)
	{
		float scalar;
		scalar = t_newScale / m_currentScale;
		m_currentScale = t_newScale;
		b2PolygonShape* shape = static_cast<b2PolygonShape*>(m_fixture->GetShape());

		for (auto index = 0; index < shape->m_count; ++index)
			shape->m_vertices[index] *= scalar;

		m_body->SetAwake(true);
	}
}

//*************************************************************

void PolygonShape::update()
{
	if (b2Shape::Type::e_polygon == m_fixture->GetType())
		updatePolygon();
}

//*************************************************************

void PolygonShape::setBodyType(b2BodyType t_type)
{
	m_body->SetType(t_type);
}

//*************************************************************

b2Vec2* PolygonShape::getPoints(uint8 const t_sides, float t_radius)
{
	b2Vec2* points = new b2Vec2[t_sides];
	float interiorAngle = 360 / t_sides;
	interiorAngle *= Deg2Rad;

	for (uint8 i = 0; i < t_sides; ++i)
		points[i] = { cos(interiorAngle * i) * t_radius, sin(interiorAngle * i) * t_radius };

	return points;
}

//*************************************************************

void PolygonShape::updatePolygon()
{
	b2PolygonShape* shape = static_cast<b2PolygonShape*>(m_fixture->GetShape());
	Vector centre = m_body->GetPosition();
	float angle = m_body->GetAngle();

	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Vector vertexPos;

	for (uint8 i = 0; i < m_vertex.getVertexCount(); ++i)
	{
		Vector vertice = shape->m_vertices[i % shape->m_count];
		Vector rotation = { (cosAngle * vertice.x) - (sinAngle * vertice.y),
							(cosAngle * vertice.y) + (sinAngle * vertice.x)};
		vertexPos = rotation + centre;
		m_vertex[i].position = vertexPos.fromWorldSpace();
	}
}