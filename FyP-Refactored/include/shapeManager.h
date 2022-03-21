#ifndef SHAPE_MANAGER_INCLUDE
#define SHAPE_MANAGER_INCLUDE

#include <iostream>
#include <vector>

#include "box2d/b2_distance_joint.h"
#include "circleShape.h"
#include "polygonShape.h"
#include "worldManager.h"
#include "vector.h"
#include "json.hpp"

using ShapeID = uint8;

class ShapeManager
{
public:
	ShapeManager();
	~ShapeManager();

	/// <summary>
	/// Allows the creation of an n sided polygon at any given size and position
	/// </summary>
	/// <param name="t_sides"> number of sides (DEFAULTS TO SQUARE) </param>
	/// <param name="t_radius"> size of the polygon </param>
	/// <param name="t_position"> center position of the polygon (IN SCREEN SPACE) </param>
	/// <returns>The ID of the created polygon in the polygon vector </returns>
	ShapeID createPolygon(uint8 t_sides = 4.0f, float t_radius = 1.0f, Vector t_position = Vector());

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
	/// Checks if there is a shape at any given position
	/// </summary>
	/// <param name="t_mousePos"> Position to check </param>
	/// <returns> The shape that's at the point NULL if no shapes</returns>
	IShape* isMouseOnShape(Vector t_mousePos);
	
	/// <summary>
	/// Updates the positions of all the shapes that have been created
	/// </summary>
	void update();

	IShape* operator[](ShapeID t_id) { return m_shapes[t_id]; }
	std::vector<IShape*>& getShapes() { return m_shapes; }

	void draw(sf::RenderWindow* t_window);

	ShapeID getID(IShape* t_shape);

	b2Joint* createDistanceJoint(ShapeID, ShapeID, float);
	b2Joint* createDistanceJoint(IShape*, IShape*, float);

	void startWorld();

	void saveWorld(jsonf& t_data);
private:

	/// <summary>
	/// Function to remove similar code through the shapes
	/// Generates a body definition that all the shapes use
	/// </summary>
	/// <param name="pos"> position of the body </param>
	/// <returns> a body definition </returns>
	b2BodyDef generateBodyDef(Vector pos);

	std::vector<IShape*> m_shapes;

	std::vector<b2DistanceJointDef*> m_distanceJoints;

	ShapeID m_currentID { 0 };

	b2World* m_world;
};

#endif