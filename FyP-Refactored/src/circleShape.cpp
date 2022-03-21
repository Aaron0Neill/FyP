#include <circleShape.h>

CircleShape::CircleShape(float t_radius)
{
	m_circle.setFillColor(sf::Color(40U,40U,40U,255U));
	m_circle.setRadius(t_radius);
	m_circle.setOrigin(t_radius, t_radius);

	m_circle.setPointCount((size_t)(t_radius * PixelsPerMetre));

	m_vertices[0].position = {t_radius, t_radius}; // centre
	m_vertices[1].position = { 0, t_radius }; // top

	m_joints.setPrimitiveType(sf::Lines);
}

//*************************************************************

void CircleShape::update()
{
	updateJoint();
	Vector pos = Vector(m_body->GetPosition()).fromWorldSpace();
	float angle = m_body->GetAngle();
	float rad = m_circle.getRadius() * 0.7f;

	m_circle.setPosition(pos);
	m_circle.setRotation(angle * Rad2Deg);

	m_vertices[0].position = pos; // centre
	m_vertices[1].position = {(cos(angle) * rad) - (sin(angle) * rad) + pos.x,
							  (cos(angle) * rad) + (sin(angle) * rad) + pos.y }; // top
}

//*************************************************************

void CircleShape::draw(sf::RenderWindow* t_window)
{
	t_window->draw(m_circle);
	t_window->draw(m_vertices,2, sf::Lines);
	t_window->draw(m_joints);
}

//*************************************************************

void CircleShape::setScale(float t_scale)
{
	if (t_scale != 0)
	{
		float scalar;
		scalar = t_scale / m_scale;
		m_scale = t_scale;
		
		b2CircleShape* shape = static_cast<b2CircleShape*>(m_fixture->GetShape());
		shape->m_radius *= scalar;

		float rad = shape->m_radius * PixelsPerMetre;
		m_circle.setRadius(rad);
		m_circle.setOrigin(rad,rad);

		m_circle.setPointCount((size_t)rad);

		m_body->SetAwake(true);
	}
}

//*************************************************************

void CircleShape::setRotation(float t_newRotation)
{
	auto pos = m_body->GetPosition();
	m_body->SetTransform(pos, t_newRotation);
}

//*************************************************************

void CircleShape::updateJoint()
{
	if (!m_body->GetJointList())return;

	auto* joint = m_body->GetJointList();
	int iter = 0;
	while (joint)
	{
		if (iter >= m_joints.getVertexCount())
			m_joints.resize(iter + 2U);
		Vector currPos = joint->joint->GetAnchorA();
		Vector jointPos = joint->joint->GetAnchorB();

		m_joints[iter++].position = currPos.fromWorldSpace();
		m_joints[iter++].position = jointPos.fromWorldSpace();
		joint = joint->next;
	}
}
