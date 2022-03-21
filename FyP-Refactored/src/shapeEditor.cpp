#include "shapeEditor.h"

ShapeEditor::ShapeEditor(sf::RenderWindow* t_window) :
	m_window(t_window), 
	m_currentState(nullptr)
{
	initFactory<CreateState>(EditState::CREATE);
	initFactory<MoveState>(EditState::MOVE);
	initFactory<ScaleState>(EditState::SCALE);
	initFactory<RotateState>(EditState::ROTATE);
	initFactory<SelectState>(EditState::SELECT);
	initFactory<DistanceJointState>(EditState::DISTANCE_JOINT);
}

//*************************************************************

void ShapeEditor::setState(EditState t_newState)
{
	m_currentState = m_factory[t_newState](m_window, m_manager);
}

//*************************************************************

void ShapeEditor::handleEvents(sf::Event& t_event)
{
	if (m_currentState)
		m_currentState->handleEvent(t_event);
}

//*************************************************************

void ShapeEditor::draw()
{
	if (m_currentState)
		m_currentState->render();
}