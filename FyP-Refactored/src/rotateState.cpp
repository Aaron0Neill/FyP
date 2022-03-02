#include "rotateState.h"

RotateState::RotateState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
}

//*************************************************************

void RotateState::handleEvent(sf::Event& e)
{
	if (sf::Event::MouseButtonPressed == e.type)
	{
		m_points[1].position = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		if (sf::Mouse::Left == e.mouseButton.button)
			if (m_selectedShape)
			{
				m_editing = true;
				m_points[0].position = Vector(m_selectedShape->getBody()->GetPosition()).fromWorldSpace();
				m_startAngle = vector2Heading(m_points[1].position - m_points[0].position);
			}
	}
	else if (sf::Event::MouseMoved == e.type)
	{
		if (m_selectedShape && m_editing)
		{
			m_points[2].position = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			float currAngle = vector2Heading(m_points[2].position - m_points[0].position);
			Vector cp = m_selectedShape->getBody()->GetPosition();
			m_selectedShape->getBody()->SetTransform(cp, currAngle);
		}
	}
	else if (sf::Event::MouseButtonReleased == e.type)
		m_editing = false;
}

//*************************************************************

void RotateState::render()
{
}
