#include "selectState.h"

SelectState::SelectState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
}

//*************************************************************

void SelectState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		m_selectedShape = m_manager->isMouseOnShape(pos);
	}
}