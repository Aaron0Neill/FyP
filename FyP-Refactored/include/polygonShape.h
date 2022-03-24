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
	/// Update the drawing of the polyon based on its body
	/// </summary>
	void update()override;
	
	/// <summary>
	/// Allow the user to change the scale of the shape
	/// </summary>
	/// <param name="t_newScale"> scale to set it to </param>
	void setScale	(float t_newScale)override;
	void setXScale	(float t_newScale)override;
	void setYScale	(float t_newScale)override;

	/// <summary>
	/// draw the PolygonShape
	/// </summary>
	/// <param name="t_window"> Window to draw it too</param>
	void draw(sf::RenderWindow* t_window)override;

	/// <summary>
	/// Convert the current shape into json and push it onto the data
	/// </summary>
	/// <param name="t_json"> Json file to add it to </param>
	void toJson(jsonf& t_json)override;

	/// <summary>
	/// Read the information from the json file and use to it make the shape
	/// </summary>
	/// <param name="t_json"></param>
	void fromJson(jsonf& t_json)override;

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