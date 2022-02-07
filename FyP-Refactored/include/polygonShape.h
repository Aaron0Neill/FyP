#ifndef POLYGON_SHAPE_INCLUDE
#define POLYGON_SHAPE_INCLUDE

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_fixture.h>
#include <SFML/Graphics/VertexArray.hpp>
#include <utils/vector.h>

class PolygonShape
{
public:
	
	/// <summary>
	/// Allow the user to change the scale of the shape
	/// </summary>
	/// <param name="t_newScale"> scale to set it to </param>
	void setScale(float t_newScale);

	/// <summary>
	/// Update the drawing of the polyon based on its body
	/// </summary>
	void update();

	/// <summary>
	/// Function to allows the user to find the current scale of the shape
	/// </summary>
	/// <returns> Returns the current scale of the shape </returns>
	float getScale() { return m_currentScale; };
private:
	PolygonShape() = default;

	/// <summary>
	/// Only update if the shape is actually polygon
	/// </summary>
	void updatePolygon();

	/// <summary>
	/// Reserver the ability to create the shape to the ShapeManager
	/// </summary>
	friend class ShapeManager;

	b2Body* m_body{ nullptr };
	b2Fixture* m_fixture{ nullptr };
	sf::VertexArray m_vertex{ sf::LinesStrip };
	float m_currentScale;
};

#endif