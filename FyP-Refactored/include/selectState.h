#ifndef SELECT_STATE_INCLUDE
#define SELECT_STATE_INCLUDE

#include "IbuildState.h"

class SelectState :
	public IBuildState
{
public:
	SelectState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~SelectState() = default;

	void handleEvent(sf::Event & e);

	void render() {};
	

private:
	void updateUI();
};

#endif