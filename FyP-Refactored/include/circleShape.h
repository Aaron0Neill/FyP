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

	void setScale(float t_scale)override;

private:
	friend class ShapeManager;
	CircleShape(float t_radius);

	sf::CircleShape m_circle;
	sf::Vertex m_vertices[2];
};

#endif