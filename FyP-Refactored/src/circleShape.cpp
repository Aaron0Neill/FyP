#include <circleShape.h>

CircleShape::CircleShape(float t_radius)
{
	m_circle.setFillColor(sf::Color::Transparent);
	m_circle.setOutlineThickness(1.0f);
	m_circle.setRadius(t_radius);
	m_circle.setOrigin(t_radius, t_radius);

	m_vertices[0].color = sf::Color::White;
	m_vertices[1].color = sf::Color::White;

	m_vertices[0].position = {t_radius, t_radius}; // centre
	m_vertices[1].position = { 0, t_radius }; // top
}

//*************************************************************

void CircleShape::update()
{
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
}
