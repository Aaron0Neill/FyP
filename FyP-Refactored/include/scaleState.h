#ifndef SCALE_STATE_INCLUDE
#define SCALE_STATE_INCLUDE

#include "IbuildState.h"
#include "utils/vectorMaths.h"

class ScaleState :
	public IBuildState
{
public:

	ScaleState(sf::RenderWindow* t_window);
	~ScaleState() = default;

	/// <summary>
	/// Handles the scaling of the shape
	/// Scale is set to the distance from the centre of the shape to the mouse position
	/// </summary>
	/// <param name="e">Current window event</param>
	void handleEvent(sf::Event& e)override;


	void render()override;

private:
	sf::Vertex m_points[2];
	bool m_editing { false };
};

#endif