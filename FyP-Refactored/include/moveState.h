#ifndef MOVE_STATE_INCLUDE
#define MOVE_STATE_INCLUDE

#include "IbuildState.h"

class MoveState : 
	public IBuildState
{
public:
	MoveState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~MoveState() = default;

	void handleEvent(sf::Event& e);

	void render() {};
private:
	bool m_editing;
};

#endif