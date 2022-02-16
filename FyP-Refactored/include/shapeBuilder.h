#ifndef SHAPE_BUILDER_INCLUDE
#define SHAPE_BUILDER_INCLUDE

#include "shapeManager.h"
#include <functional>

enum class BuilderState : uint8
{
	CREATE, 
	EDIT
};

class ShapeBuilder
{
public:
	ShapeBuilder(sf::RenderWindow* t_window);
	~ShapeBuilder()=default;

	void setState(BuilderState);

	void handleEvents(sf::Event& t_event);

	void draw();

	inline void addShapeManager(ShapeManager* t_manager) { m_manager = t_manager; }

private:

	void updatePoints(uint8 t_sides);

	void updateDrawing();

	Vector m_vertices[b2_maxPolygonVertices];
	Vector m_centrePoint;
	float m_scale { 1.f };
	sf::VertexArray m_drawing { sf::LinesStrip };
	BuilderState m_state;
	sf::RenderWindow* m_window { nullptr };
	uint8 m_currentPoints { 0U };
	ShapeManager* m_manager;
	uint8 m_lastShapeID;

	//std::function<uint8(uint8, float, Vector)> m_function;
};

#endif