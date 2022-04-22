#include "Ishape.h"

void IShape::setPosition(Vector t_pos)
{
	float angle = m_body->GetAngle();
	Vector newPos = t_pos.toWorldSpace();
	m_body->SetTransform(newPos, angle);
}

//*************************************************************

void IShape::setXPosition(float t_x)
{
	Vector pos = m_body->GetPosition();
	pos = pos.fromWorldSpace();
	pos.x = t_x;
	setPosition(pos);
}

//*************************************************************

void IShape::setYPosition(float t_y)
{
	Vector pos = m_body->GetPosition();
	pos = pos.fromWorldSpace();
	pos.y = t_y;
	setPosition(pos);
}

//*************************************************************

void IShape::setRotation(float t_rot)
{
	Vector pos = m_body->GetPosition();
	m_body->SetTransform(pos, t_rot * Deg2Rad);
}
