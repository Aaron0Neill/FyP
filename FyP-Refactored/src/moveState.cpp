#include "..\include\moveState.h"
#include "guiManager.h"

MoveState::MoveState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
	initArrows();
}

//*************************************************************

MoveState::~MoveState()
{
	GUIManager* m_guiManager = GUIManager::getInstance();
	m_guiManager->getGui()->remove(m_horizontalGroup);
	m_guiManager->getGui()->remove(m_verticalGroup);
}

//*************************************************************

void MoveState::handleEvent(sf::Event& e)
{
	if (sf::Event::MouseButtonPressed == e.type)
	{
		if (sf::Mouse::Left == e.mouseButton.button)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			if (mouse.x < 1920)
				if (!m_selectedShape)
					if (m_selectedShape = m_manager->isMouseOnShape(mouse))
					{
						m_offsetVector = Vector();
						m_selectedShape->getBody()->SetAwake(false);

						m_editingX = true;
						m_editingY = true;
					}
		}
	}
	else if (sf::Event::MouseMoved == e.type)
	{
		if (m_selectedShape)
		{
			Vector mouse = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			Vector shapePos = Vector(m_selectedShape->getBody()->GetPosition()).fromWorldSpace();
			if (m_editingX)
				shapePos.x = mouse.x - m_offsetVector.x;
			if (m_editingY)
				shapePos.y = mouse.y - m_offsetVector.y;

			m_selectedShape->setPosition(shapePos);

			updateArrows();
		}
	}
	else if (sf::Event::MouseButtonReleased == e.type)
		if (sf::Mouse::Left == e.mouseButton.button)
			if (m_selectedShape)
			{
				for (auto& widget : m_horizontalGroup->getWidgets())
					widget->getRenderer()->setOpacity(1.f);
				for (auto& widget : m_verticalGroup->getWidgets())
					widget->getRenderer()->setOpacity(1.f);

				m_selectedShape->getBody()->SetAwake(true);
				m_selectedShape = nullptr;
				m_editingX = false;
				m_editingY = false;
			}

}

//*************************************************************

void MoveState::update()
{
	updateArrows();
}

//*************************************************************

void MoveState::initArrows()
{
	GUIManager* m_guiManager = GUIManager::getInstance();
	tgui::Texture arrowTex("assets/images/Arrow.png");
	m_horizontalGroup = tgui::Group::create();
	m_verticalGroup = tgui::Group::create();

	for (auto& s : m_manager->getShapes())
	{

		Vector pos = Vector(s->getBody()->GetPosition()).fromWorldSpace();
		Vector size = { 75,50 };
		auto horizPic = tgui::Picture::create(arrowTex, true);
		horizPic->setPosition(pos.x, pos.y - size.y / 2.f);
		horizPic->setSize(size);
		horizPic->onMousePress([this, &s, horizPic, &pos](tgui::Vector2f t_mousePos) {
			m_editingX = true;
			m_selectedShape = s;
			m_offsetVector.x = t_mousePos.x - pos.x;
			horizPic->getRenderer()->setOpacity(0.25f);
			});

		auto verticalPic = tgui::Picture::create(arrowTex, true);
		verticalPic->setPosition(pos.x - size.y / 2.f, pos.y);
		verticalPic->setSize(size);
		verticalPic->setRotation(-90);
		verticalPic->onMousePress([this, &s, verticalPic, &pos](tgui::Vector2f t_mousePos) {
			m_editingY = true;
			m_selectedShape = s;
			m_offsetVector.y = pos.x - t_mousePos.x;
			verticalPic->getRenderer()->setOpacity(0.25f);
			});

		m_horizontalGroup->add(horizPic);
		m_verticalGroup->add(verticalPic);
		if (s->getFixture()->GetShape()->GetType() == b2Shape::Type::e_edge)
		{
			horizPic->setVisible(false);
			verticalPic->setVisible(false);
		};
	}

	m_guiManager->getGui()->add(m_horizontalGroup, "HorizontalGroup");
	m_guiManager->getGui()->add(m_verticalGroup, "VerticalGroup");
}

//*************************************************************

void MoveState::updateArrows()
{
	int size = m_manager->getShapes().size();
	for (int i = 0; i < size; ++i)
	{
		Vector pos = Vector((*m_manager)[i]->getBody()->GetPosition()).fromWorldSpace();
		Vector size = m_horizontalGroup->getWidgets()[i]->getSize();
		m_horizontalGroup->getWidgets()[i]->setPosition({ pos.x, pos.y - size.y / 2.f });
		m_verticalGroup->getWidgets()[i]->setPosition({ pos.x - size.y / 2.f, pos.y });
	}
}
