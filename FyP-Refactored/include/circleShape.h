#ifndef CIRCLE_SHAPE_INCLUDE
#define CIRCLE_SHAPE_INCLUDE

#include "Ishape.h"

#include <box2d/b2_circle_shape.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <utils/vector.h>
#include <iostream>

class CircleShape : 
	public IShape
{
public:
	/// <summary>
	/// Update the position of the cicle as well as the rotation of the lines 
	/// </summary>
	void update()override;

	/// <summary>
	/// Draw the circle shape
	/// </summary>
	/// <param name="t_window"> Window to render to </param>
	void draw(sf::RenderWindow* t_window)override;

	/// <summary>
	/// Set Function
	/// </summary>
	void setScale	(float t_scale)		override;
	void setXScale	(float t_newScale)	override;
	void setYScale	(float t_newScale)	override;

	/// <summary>
	/// Conversion to and from JSON 
	/// </summary>
	/// <param name="t_json"> Where you wanna append all the information </param>
	void toJson		(jsonf& t_json)		override;
	void fromJson	(jsonf& t_json)		override;

	inline sf::CircleShape getDrawing() { return m_circle; }

private:
	friend class ShapeManager;
	CircleShape(float t_radius);

	sf::CircleShape m_circle;
	sf::Vertex m_vertices[2];
};

#endif