#include "createState.h"
#include <iostream>

IShape* IBuildState::m_selectedShape { nullptr };

CreateState::CreateState(sf::RenderWindow* t_window, ShapeManager* t_manager) :
	IBuildState(t_window, t_manager),
	m_centrePoint({})
{
	m_circle.setFillColor({ 40U,40U,40U,255U });
	m_circle.setRadius(PixelsPerMetre);
	m_circle.setOrigin({ PixelsPerMetre, PixelsPerMetre });
}

//*************************************************************

void CreateState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		m_centrePoint = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		updateDrawing();
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code >= sf::Keyboard::Num3 && e.key.code <= sf::Keyboard::Num9)
			updatePoints(e.key.code - sf::Keyboard::Num0);	
		else if (e.key.code == sf::Keyboard::Escape)
		{
			m_drawingCircle = false;
			m_drawingPolygon = false;
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
			if (m_centrePoint.x < (1920.f - 400.f))
				if (m_drawingPolygon)
					m_manager->createPolygon(m_currentPoints, 1, m_centrePoint);
				else if (m_drawingCircle)
					m_manager->createCircle(1, m_centrePoint);
	}
}

//*************************************************************

void CreateState::render()
{ 
	if (m_drawingPolygon)
		m_window->draw(m_drawing);
	else if (m_drawingCircle)
		m_window->draw(m_circle);
}

//*************************************************************

void CreateState::updatePoints(uint8 t_sides)
{
	if (t_sides >= 3 && t_sides <= 8)
	{
		m_drawingPolygon = true;
		m_drawingCircle = false;

		auto points = PolygonShape::getPoints(t_sides, 1);

		for (int i = 0; i < t_sides; ++i)
			m_vertices[i] = Vector(points[i]);

		m_currentPoints = t_sides;
		m_drawing.resize(t_sides + 1);
		delete points;
	}
	else if (t_sides == 9)
	{
		m_drawingPolygon = false;
		m_drawingCircle = true;
	}

	updateDrawing();
}

//*************************************************************

void CreateState::updateDrawing()
{
	if (m_drawingPolygon)
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
	else if (m_drawingCircle)
	{
		m_circle.setPosition(m_centrePoint);
	}
}
