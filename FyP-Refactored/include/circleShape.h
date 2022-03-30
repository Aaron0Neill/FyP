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

	void update()override;

	void draw(sf::RenderWindow* t_window)override;

	/// <summary>
	/// Set Function
	/// </summary>
	void setScale	(float t_scale)		override;
	void setXScale	(float t_newScale)	override;
	void setYScale	(float t_newScale)	override;

	void toJson		(jsonf& t_json)		override;
	void fromJson	(jsonf& t_json)		override;

private:
	friend class ShapeManager;
	CircleShape(float t_radius);

	sf::CircleShape m_circle;
	sf::Vertex m_vertices[2];
};

#endif