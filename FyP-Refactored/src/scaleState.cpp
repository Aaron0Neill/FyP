#include "scaleState.h"

ScaleState::ScaleState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
	m_points[0].color = sf::Color::Black;
	m_points[1].color = sf::Color::Black;
}

//*************************************************************

void ScaleState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		m_points[1] = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		if (e.mouseButton.button == sf::Mouse::Left)
			if (m_selectedShape)
			{
				m_selectedShape->getBody()->SetAwake(false);
				m_points[0].position = Vector(m_selectedShape->getBody()->GetPosition()).fromWorldSpace();
				m_editing = true;
			}
	}
	else if (e.type == sf::Event::MouseMoved)
	{
		if (m_selectedShape && m_editing)
		{
			m_points[1] = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			float scale = vectorLength(m_points[0].position - m_points[1].position) / PixelsPerMetre;
			m_selectedShape->setScale(scale);
			m_selectedShape->getBody()->SetAwake(false);
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased) 
	{
		if (m_selectedShape)
			m_selectedShape->getBody()->SetAwake(true);
		m_editing = false;
		
	}
}

//*************************************************************

void ScaleState::render()
{
	if (m_selectedShape && m_editing)
		m_window->draw(m_points, 2, sf::Lines);
}
