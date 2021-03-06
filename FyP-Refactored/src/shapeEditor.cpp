#include "shapeEditor.h"

ShapeEditor::ShapeEditor(sf::RenderWindow* t_window) :
	m_window(t_window),
	m_currentState(nullptr),
	m_manager(*ShapeManager::getInstance())
{
	initFactory<CreateState>(EditState::CREATE);
	initFactory<MoveState>(EditState::MOVE);
	initFactory<ScaleState>(EditState::SCALE);
	initFactory<RotateState>(EditState::ROTATE);
	initFactory<SelectState>(EditState::SELECT);
	initFactory<DistanceJointState>(EditState::DISTANCE_JOINT);
	initFactory<WheelJointState>(EditState::WHEEL_JOINT);
}

//*************************************************************

void ShapeEditor::setState(EditState t_newState)
{
	m_currentState = m_factory[t_newState](m_window);
}

//*************************************************************

void ShapeEditor::handleEvents(sf::Event& t_event)
{
	if (m_currentState)
		m_currentState->handleEvent(t_event);
}

//*************************************************************

void ShapeEditor::update()
{
	if (m_currentState)
		m_currentState->update();
}

//*************************************************************

void ShapeEditor::draw()
{
	if (m_currentState)
		m_currentState->render();
}