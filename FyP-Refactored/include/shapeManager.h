#ifndef SHAPE_MANAGER_INCLUDE
#define SHAPE_MANAGER_INCLUDE

#include <utils/vector.h>
#include <vector>

#include <polygonShape.h>
#include <circleShape.h>

#include <box2d/b2_circle_shape.h>
#include <worldManager.h>

#include <iostream>
using ShapeID = uint8;

class ShapeManager
{
public:
	ShapeManager();
	~ShapeManager() = default;

	/// <summary>
	/// Allows the creation of an n sided polygon at any given size and position
	/// </summary>
	/// <param name="t_sides"> number of sides (DEFAULTS TO SQUARE) </param>
	/// <param name="t_radius"> size of the polygon </param>
	/// <param name="t_position"> center position of the polygon (IN SCREEN SPACE) </param>
	/// <returns>The ID of the created polygon in the polygon vector </returns>
	ShapeID createPolygon(uint8 const t_sides = 4.0f, float t_radius = 1.0f, Vector t_position = Vector());

	/// <summary>
	/// Allows for the creation of a circle of any size in any position
	/// </summary>
	/// <param name="t_radius"> size of the circle </param>
	/// <param name="t_position"> center of the circle (IN SCREEN SPACE) </param>
	/// <returns> The ID of the created circle in the circle vector </returns>
	ShapeID createCircle(float t_radius = 1.0f, Vector t_position = Vector());

	/// <summary>
	/// Creates an edge shape that will be placed at the two points
	/// (BOTH IN SCREEN SPACE)
	/// </summary>
	/// <param name="t_p1"> Pixel co-ordinates of the first point </param>
	/// <param name="t_p2"> Pixel co-ordinates of the second point </param>
	/// <returns> The ID of the created edge in the polygonVector </returns>
	ShapeID createEdge(Vector t_p1, Vector t_p2);
	
	/// <summary>
	/// Updates the positions of all the shapes that have been created
	/// </summary>
	void update();

	/// <summary>
	/// Allows classes outside to get a polygon at a given index 
	/// </summary>
	/// <param name="t_index"> index of the shape that will be returned </param>
	/// <returns> The polygon at the index (NO ERROR CHECKING) </returns>
	PolygonShape* getPolygon(ShapeID t_index) { return &m_polygons[t_index]; }

	/// <summary>
	/// Allows classes outside to get a circle at a given index 
	/// </summary>
	/// <param name="t_index"> index of the shape that will be returned </param>
	/// <returns> The circle at the index (NO ERROR CHECKING) </returns>
	CircleShape* getCircle(ShapeID t_index) { return &m_circles[t_index]; }

	void draw(sf::RenderWindow* t_window);
private:
	/// <summary>
	/// Generates points for a n sided polygon at a given size 
	/// </summary>
	/// <param name="t_sides"> number of sides on the polygon </param>
	/// <param name="t_radius"> size of the polygon </param>
	/// <returns> points for the size </returns>
	b2Vec2* getPoints(uint8 const t_sides, float t_radius);

	/// <summary>
	/// Function to remove similar code through the shapes
	/// Generates a body definition that all the shapes use
	/// </summary>
	/// <param name="pos"> position of the body </param>
	/// <returns> a body definition </returns>
	b2BodyDef generateBodyDef(Vector pos);

	std::vector<PolygonShape> m_polygons;
	std::vector<CircleShape> m_circles;

	ShapeID m_polygonIndex{ 0 };
	ShapeID m_circleIndex{ 0 };

	b2World* m_world;
};

#endif