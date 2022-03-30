#ifndef DISTANCE_JOINT_STATE_INCLUDE
#define DISTANCE_JOINT_STATE_INCLUDE

#include "IbuildState.h"
#include "utils/vectorMaths.h"

class DistanceJointState :
	public IBuildState
{
public:
	DistanceJointState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~DistanceJointState() = default;

	/// <summary>
	/// Handle to events when creating a distance joint. 
	/// </summary>
	/// <param name="e"> Current event on the screen </param>
	void handleEvent(sf::Event& e)override;

	/// <summary>
	/// Render relevant information for the distance joint
	/// </summary>
	void render()override;
private:
	IShape* m_bodyA { nullptr };
	IShape* m_bodyB { nullptr };
};

#endif