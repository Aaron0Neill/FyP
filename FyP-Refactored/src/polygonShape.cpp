#include <polygonShape.h>

void PolygonShape::setScale(float t_newScale)
{
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
							(cosAngle * vertice.y) + (sinAngle * vertice.x) };
		vertexPos = rotation + centre;
		m_vertex[i].position = vertexPos.fromWorldSpace();
	}
}