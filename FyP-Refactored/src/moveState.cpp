#include "..\include\moveState.h"

MoveState::MoveState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
}

void MoveState::handleEvent(sf::Event& e)
{
	if (sf::Event::MouseButtonPressed == e.type)
	{
		if (sf::Mouse::Left == e.mouseButton.button)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			if (m_selectedObject = m_manager->isMouseOnShape(mouse))
			{
				m_objectSelected = true;
			}
		}
	}
	else if (sf::Event::MouseMoved == e.type)
	{
		if (m_objectSelected)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			m_selectedObject->setPosition(mouse);
		}
	}
	else if (sf::Event::MouseButtonReleased == e.type)
	{
		if (sf::Mouse::Left == e.mouseButton.button)
		{
			m_objectSelected = false;
			if (m_selectedObject)
			{
				m_selectedObject->getBody()->SetAwake(true);
				m_selectedObject = nullptr;
			}
		}
	}

}
