#include "shapeBuilder.h"

ShapeBuilder::ShapeBuilder(sf::RenderWindow* t_window) :
	m_window(t_window), 
	m_currentState(nullptr)
{
	initFactory<CreateState>(BuilderState::CREATE);
	initFactory<MoveState>(BuilderState::MOVE);
	initFactory<ScaleState>(BuilderState::SCALE);
	initFactory<RotateState>(BuilderState::ROTATE);
}

//*************************************************************

void ShapeBuilder::setState(BuilderState t_newState)
{
	m_currentState = m_factory[t_newState](m_window, m_manager);
}

//*************************************************************

void ShapeBuilder::handleEvents(sf::Event& t_event)
{
	if (m_currentState)
		m_currentState->handleEvent(t_event);
}

//*************************************************************

void ShapeBuilder::draw()
{
	if (m_currentState)
		m_currentState->render();
}