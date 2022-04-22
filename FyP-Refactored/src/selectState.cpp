#include "selectState.h"
#include "guiManager.h"

SelectState::SelectState(sf::RenderWindow* t_window) : 
	IBuildState(t_window)
{
	if (m_selectedShape)
		updateUI();
}

//*************************************************************

void SelectState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		if (pos.x < 1920)
			if (m_selectedShape = m_manager->isMouseOnShape(pos))
			{// update UI
				tgui::Gui* gui = GUIManager::getInstance()->getGui();
				ShapeID id = m_manager->getID(m_selectedShape);
				gui->get<tgui::Label>("ShapeID")->setText("Current Shape id: " + std::to_string(id));
				updateUI();
			}
	}
}

void SelectState::updateUI()
{
	GUIManager* gui = GUIManager::getInstance();
	gui->updateSelectedShape(m_selectedShape);
}
