#ifndef CREATE_STATE_INCLUDE
#define CREATE_STATE_INCLUDE

#include "IbuildState.h"

enum class ShapeType : uint8_t
{
	NONE = 255,
	EDGE = 2,
	TRIANGLE = 3,
	SQUARE = 4,
	PENTAGON = 5,
	HEXAGON = 6,
	SEPTAGON = 7,
	OCTAGON = 8,
	CIRCLE = 9
};

class CreateState : 
	public IBuildState
{
public:
	CreateState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~CreateState()=default;

	void handleEvent(sf::Event& e)override;

	void render()override;

	void updateShape(ShapeType t_sides);
private:

	void updateDrawing();

	void showShape();

	Vector m_vertices[b2_maxPolygonVertices];
	Vector m_centrePoint;
	float m_scale{ 1.f };
	sf::VertexArray m_drawing{ sf::LinesStrip };
	sf::CircleShape m_circle;
	uint8 m_currentPoints{ 0U };	
	ShapeType m_currentShape { ShapeType::NONE };
};

#endif