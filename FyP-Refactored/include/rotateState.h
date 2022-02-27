#ifndef ROTATE_STATE_INCLUDE
#define ROTATE_STATE_INCLUDE

#include "IbuildState.h"
#include "utils/vectorMaths.h"

class RotateState :
	public IBuildState
{
public:
	RotateState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~RotateState() = default;

	void handleEvent(sf::Event& e)override;

	void render()override;
private:
	sf::Vertex m_points[3];
	float m_startAngle{ 0 };
	bool m_editing {false};
};

#endif