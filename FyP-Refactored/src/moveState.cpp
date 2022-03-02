#include "..\include\moveState.h"

MoveState::MoveState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
}

//*************************************************************

void MoveState::handleEvent(sf::Event& e)
{
	if (sf::Event::MouseButtonPressed == e.type)
	{
		if (sf::Mouse::Left == e.mouseButton.button)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			if (mouse.x < 1520)
				if (m_selectedShape = m_manager->isMouseOnShape(mouse))
				{
					m_selectedShape->getBody()->SetAwake(false);
					m_editing = true;
				}
		}
	}
	else if (sf::Event::MouseMoved == e.type)
	{
		if (m_selectedShape && m_editing)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			m_selectedShape->setPosition(mouse);
		}
	}
	else if (sf::Event::MouseButtonReleased == e.type)
		if (sf::Mouse::Left == e.mouseButton.button)
			if (m_selectedShape)
			{
				m_selectedShape->getBody()->SetAwake(true);
				m_editing = false;
			}

}
