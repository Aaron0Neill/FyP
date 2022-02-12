#ifndef CIRCLE_SHAPE_INCLUDE
#define CIRCLE_SHAPE_INCLUDE

#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <utils/vector.h>
#include <iostream>

class CircleShape
{
public:

	void update();
	void draw(sf::RenderWindow* t_window);

	b2Body* getBody() { return m_body; }
private:
	CircleShape(float t_radius);

	friend class ShapeManager;

	b2Body* m_body{ nullptr };
	b2Fixture* m_fixture{ nullptr };
	sf::CircleShape m_circle;
	sf::Vertex m_vertices[2];
};

#endif