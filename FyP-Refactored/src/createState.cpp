#include "createState.h"
#include <iostream>

CreateState::CreateState(sf::RenderWindow* t_window, ShapeManager* t_manager) :
	IBuildState(t_window, t_manager),
	m_centrePoint({})
{
}

void CreateState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		m_centrePoint = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		updateDrawing();
		//if (m_state != BuilderState::CREATE)
		//{
		//	Vector cp = m_manager->getPolygon(m_lastShapeID)->getBody()->GetPosition();

		//	float scale = vectorLength(m_centrePoint - cp.fromWorldSpace()) / PixelsPerMetre;
		//	m_manager->getPolygon(m_lastShapeID)->setScale(scale);
		//}
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code >= sf::Keyboard::Num3 && e.key.code <= sf::Keyboard::Num8)
			updatePoints(e.key.code - sf::Keyboard::Num0);
		else if (e.key.code == sf::Keyboard::Escape)
		{
			m_currentPoints = 0;
			m_drawing.clear();
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (m_currentPoints >=3 && m_currentPoints <= 8)
			if (e.mouseButton.button == sf::Mouse::Left)
				if (m_centrePoint.x < (1920.f - 400.f))
					m_manager->createPolygon(m_currentPoints, 1, m_centrePoint);
	}
}

void CreateState::render()
{
	m_window->draw(m_drawing);
}

void CreateState::updatePoints(uint8 t_sides)
{
	auto points = PolygonShape::getPoints(t_sides, 1);

	for (int i = 0; i < t_sides; ++i)
		m_vertices[i] = Vector(points[i]);

	m_currentPoints = t_sides;
	m_drawing.resize(t_sides + 1);
	delete points;
	updateDrawing();
}

void CreateState::updateDrawing()
{
	if (m_currentPoints != 0)
	{
		float cosAngle = cos(0.f);
		float sinAngle = sin(0.f);
		Vector vertexPos;

		for (uint8 i = 0; i < m_currentPoints + 1; ++i)
		{
			Vector vertice = m_vertices[i % m_currentPoints];
			Vector rotation = { (cosAngle * vertice.x) - (sinAngle * vertice.y),
								(cosAngle * vertice.y) + (sinAngle * vertice.x) };
			vertexPos = rotation + m_centrePoint.toWorldSpace();
			m_drawing[i].position = vertexPos.fromWorldSpace();

			m_drawing[i].color = sf::Color::Black;
		}
	}
}
