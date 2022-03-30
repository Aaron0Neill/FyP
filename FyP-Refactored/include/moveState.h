#ifndef MOVE_STATE_INCLUDE
#define MOVE_STATE_INCLUDE

#include "IbuildState.h"

#include <unordered_map>
#include <TGUI/Widgets/Group.hpp>

class MoveState : 
	public IBuildState
{
public:
	MoveState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~MoveState();

	void handleEvent(sf::Event& e);
	void render() {};

private:

	/// <summary>
	/// initialise the arrows 
	/// </summary>
	void initArrows();

	/// <summary>
	/// update the position of the arrows 
	/// </summary>
	void updateArrows();

	bool m_editingY { false };
	bool m_editingX { false };
	Vector m_offsetVector;
	tgui::Group::Ptr m_horizontalGroup;
	tgui::Group::Ptr m_verticalGroup;
};

#endif