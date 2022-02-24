#ifndef CREATE_STATE_INCLUDE
#define CREATE_STATE_INCLUDE

#include "IbuildState.h"

class CreateState : 
	public IBuildState
{
public:
	CreateState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~CreateState()=default;

	void handleEvent(sf::Event& e)override;

	void render()override;

	void updatePoints(uint8 t_sides);
private:

	void updateDrawing();

	Vector m_vertices[b2_maxPolygonVertices];
	Vector m_centrePoint;
	float m_scale{ 1.f };
	sf::VertexArray m_drawing{ sf::LinesStrip };
	uint8 m_currentPoints{ 0U };
};

#endif