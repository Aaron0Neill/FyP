#ifndef SELECT_STATE_INCLUDE
#define SELECT_STATE_INCLUDE

#include "IbuildState.h"

class SelectState :
	public IBuildState
{
public:
	SelectState(sf::RenderWindow* t_window);
	~SelectState() = default;

	/// <summary>
	/// Handles the selection of shapes. Will check if the user has clicked on any shapes
	/// </summary>
	/// <param name="e">Current window event</param>
	void handleEvent(sf::Event & e);
	void render() {};
	
private:
	/// <summary>
	/// if the user did click on a shape this will update the GUI manager
	/// with the relevant shape.
	/// </summary>
	void updateUI();
};

#endif