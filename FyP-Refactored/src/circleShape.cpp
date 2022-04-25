#include <circleShape.h>

CircleShape::CircleShape() : CircleShape(1.f)
{
}

//*************************************************************

CircleShape::CircleShape(float t_radius)
{
	m_circle.setFillColor(sf::Color(40U,40U,40U,255U));
	m_circle.setRadius(t_radius);
	m_circle.setOrigin(t_radius, t_radius);

	m_circle.setPointCount((size_t)(t_radius));

	m_vertices[0].position = {t_radius, t_radius}; // centre
	m_vertices[1].position = { 0, t_radius }; // top
}

//*************************************************************

CircleShape::CircleShape(const CircleShape& t_copy)
{
	m_name		= t_copy.m_name;
	m_tag		= t_copy.m_tag;
	m_destroy	= t_copy.m_destroy;
	m_scale		= t_copy.m_scale;
	m_circle	= t_copy.m_circle;
}

//*************************************************************

void CircleShape::operator=(const CircleShape& t_other)
{
	m_name		= t_other.m_name;
	m_tag		= t_other.m_tag;
	m_destroy	= t_other.m_destroy;
	m_scale		= t_other.m_scale;
	m_circle	= t_other.m_circle;
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
	if (m_visible)
	{
		t_window->draw(m_circle);
		t_window->draw(m_vertices,2, sf::Lines);
	}
}

//*************************************************************

void CircleShape::setScale(float t_scale)
{
	if (t_scale != 0)
	{
		float scalar;
		scalar = t_scale / m_scale.x;
		m_scale.x = t_scale;
		
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

void CircleShape::toJson(jsonf& t_json)
{
	t_json["Name"] = m_name;
	t_json["ShapeType"] = m_fixture->GetType();

	Vector pos = m_body->GetPosition();
	pos = pos.fromWorldSpace();
	t_json["Centre"] = { pos.x, pos.y };

	t_json["Scale"] = m_scale.x;
	t_json["Rotation"] = m_body->GetAngle() * Rad2Deg;
	t_json["BodyType"] = m_body->GetType();
}

//*************************************************************

void CircleShape::fromJson(jsonf& t_json)
{
	m_name = t_json["Name"].get<std::string>();

	auto posPtr = t_json["Centre"].begin();

	float xPos = (*posPtr++);
	float yPos = *posPtr;

	setPosition({xPos, yPos});

	float scale = *t_json["Scale"].begin();
	setScale(scale);

	float rot = t_json["Rotation"].get<float>();
	setRotation(rot);

	b2BodyType type = t_json["BodyType"].get<b2BodyType>();
	setBodyType(type);
}
