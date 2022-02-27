#ifndef SCALE_STATE_INCLUDE
#define SCALE_STATE_INCLUDE

#include "IbuildState.h"
#include "utils/vectorMaths.h"

class ScaleState :
	public IBuildState
{
public:
	ScaleState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~ScaleState() = default;

	void handleEvent(sf::Event& e)override;

	void render()override;
private:
	sf::Vertex m_points[2];
	bool m_editing { false };
};

#endif