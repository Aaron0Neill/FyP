#ifndef ROTATE_STATE_INCLUDE
#define ROTATE_STATE_INCLUDE

#include "IbuildState.h"
#include "utils/vectorMaths.h"

class RotateState :
	public IBuildState
{
public:
	RotateState(sf::RenderWindow* t_window);
	~RotateState() = default;

	/// <summary>
	/// Handles the rotation of the selected shape, 
	/// rotates based on angle from the original click
	/// </summary>
	/// <param name="e"></param>
	void handleEvent(sf::Event& e)override;

	/// <summary>
	/// Renders a preview for the user to see 
	/// </summary>
	void render()override;

private:
	sf::Vertex m_points	[3]; // points that are of interest, cp of the shape, initial click, updated mouse pos
	float m_startAngle	{ 0 };
	bool m_editing		{false};
};

#endif