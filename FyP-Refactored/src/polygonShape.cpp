#include <polygonShape.h>

void PolygonShape::setScale(float t_newScale)
{
	setXScale(t_newScale);
	setYScale(t_newScale);
}

//*************************************************************

void PolygonShape::setXScale(float t_newScale)
{
	if (t_newScale != 0)
	{
		float scalar;
		scalar = t_newScale / m_scale.x;
		m_scale.x = t_newScale;
		b2PolygonShape* shape = static_cast<b2PolygonShape*>(m_fixture->GetShape());

		for (auto index = 0; index < shape->m_count; ++index)
			shape->m_vertices[index].x *= scalar;

		m_body->SetAwake(true);
	}
}

//*************************************************************

void PolygonShape::setYScale(float t_newScale)
{
	if (t_newScale != 0)
	{
		float scalar;
		scalar = t_newScale / m_scale.y;
		m_scale.y = t_newScale;
		b2PolygonShape* shape = static_cast<b2PolygonShape*>(m_fixture->GetShape());

		for (auto index = 0; index < shape->m_count; ++index)
			shape->m_vertices[index].y *= scalar;

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

void PolygonShape::draw(sf::RenderWindow* t_window)
{
	t_window->draw(m_vertex, m_state);
}

//*************************************************************

void PolygonShape::toJson(jsonf& t_json)
{
	TextureManager* tm = TextureManager::getInstance();
	b2Shape::Type type = m_fixture->GetType();

	t_json["ShapeType"] = type;
	t_json["Name"] = m_name;
	t_json["Tag"] = m_tag;

	if (m_state.texture)
		t_json["Texture"] = tm->findName(m_state.texture);

	if (type == b2Shape::Type::e_polygon)
	{
		Vector pos = m_body->GetPosition();
		pos = pos.fromWorldSpace();
		t_json["Centre"] = { pos.x, pos.y };
		t_json["PolyCount"] = static_cast<b2PolygonShape*>(m_fixture->GetShape())->m_count;
	}
	else
	{
		Vector pos1 = static_cast<b2EdgeShape*>(m_fixture->GetShape())->m_vertex1;
		Vector pos2 = static_cast<b2EdgeShape*>(m_fixture->GetShape())->m_vertex2;
		pos1 = pos1.fromWorldSpace();
		pos2 = pos2.fromWorldSpace();

		t_json["Points"] = { pos1.x , pos1.y , pos2.x, pos2.y };
	}
	t_json["Scale"] = { m_scale.x, m_scale.y };
	t_json["Rotation"] = m_body->GetAngle() * Rad2Deg;
	t_json["BodyType"] = m_body->GetType();
}

//*************************************************************

void PolygonShape::fromJson(jsonf& t_json)
{
	m_name = t_json["Name"].get<std::string>();
	if (t_json.contains("Tag"))
		m_tag = t_json["Tag"].get<std::string>();

	auto posPtr = t_json["Centre"].begin();
	float x = (*posPtr++);
	float y = (*posPtr);

	if (!m_state.texture)
	{
		int32 polyCount = t_json["PolyCount"].get<int32>();

		if (polyCount == 4)
		{
			float size = 1.f / 1.5f;
			static_cast<b2PolygonShape*>(m_fixture->GetShape())->SetAsBox(size,size);
		}
		else
		{
			auto points = getPoints(polyCount, 1);
			static_cast<b2PolygonShape*>(m_fixture->GetShape())->Set(points, polyCount);
			delete points;
		}

		m_vertex.resize(polyCount + 1);

		for (size_t i = 0; i < polyCount + 1; ++i)
			m_vertex[i].color = sf::Color(40U, 40U, 40U, 255U);
	}

	setPosition({ x,y });
		
	float scaleX, scaleY;
	auto scalePtr = t_json["Scale"].begin();
	scaleX = (*scalePtr++);
	scaleY = *scalePtr;

	setXScale(scaleX);
	setYScale(scaleY);

	float rotation = t_json["Rotation"].get<float>();
	setRotation(rotation);

	auto bodyType = t_json["BodyType"].get<b2BodyType>();
	setBodyType(bodyType);

}

//*************************************************************

b2Vec2* PolygonShape::getPoints(uint8 const t_sides, float t_radius)
{
	b2Vec2* points = new b2Vec2[t_sides];
	float interiorAngle = (float)(360 / t_sides);
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
		vertexPos = { rotation + centre };
		m_vertex[i].position = vertexPos.fromWorldSpace();
	}
}