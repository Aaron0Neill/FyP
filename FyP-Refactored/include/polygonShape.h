#ifndef POLYGON_SHAPE_INCLUDE
#define POLYGON_SHAPE_INCLUDE

#include "Ishape.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <SFML/Graphics/VertexArray.hpp>
#include <utils/vector.h>
#include <stdlib.h>

class PolygonShape : 
	public IShape
{
public:
	
	/// <summary>
	/// Allow the user to change the scale of the shape
	/// </summary>
	/// <param name="t_newScale"> scale to set it to </param>
	void setScale(float t_newScale)override;

	void setRotation(float t_newRotation)override;

	/// <summary>
	/// Update the drawing of the polyon based on its body
	/// </summary>
	void update()override;

	void draw(sf::RenderWindow* t_window)override;

	b2Body* getBody() { return m_body; }

	/// <summary>
	/// Generates points for a n sided polygon at a given size 
	/// </summary>
	/// <param name="t_sides"> number of sides on the polygon </param>
	/// <param name="t_radius"> size of the polygon </param>
	/// <returns> points for the size </returns>
	static b2Vec2* getPoints(uint8 const t_sides, float t_radius);
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

	sf::VertexArray m_vertex{ sf::TriangleFan };
};

#endif