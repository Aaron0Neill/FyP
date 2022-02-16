#include "shapeBuilder.h"

ShapeBuilder::ShapeBuilder(sf::RenderWindow* t_window) :
	m_window(t_window), 
	m_state(BuilderState::CREATE)
{
	updatePoints(4U);
}

//*************************************************************

void ShapeBuilder::setState(BuilderState t_newState)
{
	m_state = t_newState;
}

//*************************************************************

void ShapeBuilder::handleEvents(sf::Event& t_event)
{
	if (t_event.type == sf::Event::MouseMoved)
	{
		m_centrePoint = sf::Mouse::getPosition(*m_window);
		updateDrawing();
	}
	else if (t_event.type == sf::Event::KeyPressed)
	{
		if (m_state == BuilderState::CREATE)
		{
			if (t_event.key.code >= sf::Keyboard::Num3 && t_event.key.code <= sf::Keyboard::Num8)
			{
				updatePoints(t_event.key.code - sf::Keyboard::Num0);
				updateDrawing();
			}
			if (t_event.key.code == sf::Keyboard::P)
			{
				setState(BuilderState::EDIT);
			}
		}
		else
		{
			if (t_event.key.code == sf::Keyboard::Num4)
				m_manager->getPolygon(m_lastShapeID)->setScale(4.f);
			else if (t_event.key.code == sf::Keyboard::Num1)
				m_manager->getPolygon(m_lastShapeID)->setScale(1.f);

		}
	}
	else if (t_event.type == sf::Event::MouseButtonPressed)
	{
		if (t_event.mouseButton.button == sf::Mouse::Left)
			m_lastShapeID = m_manager->createPolygon(m_currentPoints, 1, m_centrePoint);
	}
}

//*************************************************************

void ShapeBuilder::draw()
{
	if (m_state == BuilderState::CREATE)
		m_window->draw(m_drawing);
}

//*************************************************************

void ShapeBuilder::updatePoints(uint8 t_sides)
{
	auto points = PolygonShape::getPoints(t_sides, 1);

	for (int i = 0; i < t_sides; ++i)
		m_vertices[i] = Vector(points[i]);
	
	m_currentPoints = t_sides;
	m_drawing.resize(t_sides + 1);
	delete points;
}

//*************************************************************

void ShapeBuilder::updateDrawing()
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
	}
}
