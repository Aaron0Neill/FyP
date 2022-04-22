#ifndef SHAPE_MANAGER_INCLUDE
#define SHAPE_MANAGER_INCLUDE

#include <iostream>
#include <vector>

#include "box2d/b2_distance_joint.h"
#include "box2d/b2_wheel_joint.h"
#include "box2d/b2_world_callbacks.h"
#include "TextureManager.h"
#include "circleShape.h"
#include "polygonShape.h"
#include "vector.h"
#include "json.hpp"

class ContactListener;

using ShapeID = uint8;

class ShapeManager
{
public:
	static ShapeManager* getInstance();
	ShapeManager(const ShapeManager&) = delete;
	void operator=(const ShapeManager&) = delete;

	void setWorld(b2World* t_world);

	/// <summary>
	/// @Brief
	/// Allows the creation of an n sided polygon at any given size and position
	/// </summary>
	/// <param name="t_sides"> number of sides (DEFAULTS TO SQUARE) </param>
	/// <param name="t_radius"> size of the polygon </param>
	/// <param name="t_position"> center position of the polygon (IN SCREEN SPACE) </param>
	/// <returns>The ID of the created polygon in the polygon vector </returns>
	ShapeID createPolygon(uint8 t_sides = 4.0f, float t_radius = 1.0f, Vector t_position = Vector());

	/// <summary>
	/// @Brief
	/// Allows for the creation of a circle of any size in any position
	/// </summary>
	/// <param name="t_radius"> size of the circle </param>
	/// <param name="t_position"> center of the circle (IN SCREEN SPACE) </param>
	/// <returns> The ID of the created circle in the circle vector </returns>
	ShapeID createCircle(float t_radius = 1.0f, Vector t_position = Vector());

	/// <summary>
	/// @Brief
	/// Creates an edge shape that will be placed at the two points
	/// (BOTH IN SCREEN SPACE)
	/// </summary>
	/// <param name="t_p1"> Pixel co-ordinates of the first point </param>
	/// <param name="t_p2"> Pixel co-ordinates of the second point </param>
	/// <returns> The ID of the created edge in the polygonVector </returns>
	ShapeID createEdge(Vector t_p1 = Vector(), Vector t_p2 = Vector(10,0));

	/// <summary>
	/// @Brief
	/// Checks if there is a shape at any given position
	/// </summary>
	/// <param name="t_mousePos"> Position to check </param>
	/// <returns> The shape that's at the point NULL if no shapes</returns>
	IShape* isMouseOnShape(Vector t_mousePos);

	ShapeID createSprite(Texture t_texture, Vector t_centre);
	ShapeID createSprite(std::string t_textureName, Vector t_centre);
	
	/// <summary>
	/// @Brief
	/// Updates the positions of all the shapes that have been created
	/// </summary>
	void update();

	/// <summary>
	/// @Brief
	/// operator [] allows the user to index into the sapes using a shape id 
	/// </summary>
	/// <param name="t_id"> Shape ID </param>
	/// <returns> Shape at the given ID </returns>
	IShape* operator[](const ShapeID& t_id) { return m_shapes[t_id]; } 

	/// <summary>
	/// @Brief
	/// Allows the user to search for a shape by name
	/// </summary>
	/// <param name="t_name"> Name of the shape </param>
	/// <returns> The shape at the name </returns>
	IShape* find(const std::string& t_name);

	/// <summary>
	/// @Brief
	/// Allows the user to get all the shapes
	/// </summary>
	/// <returns> Vector holding all the shapes</returns>
	std::vector<IShape*>& getShapes() { return m_shapes; }

	std::vector<b2Joint*> getJoints() { return m_joints; }

	/// <summary>
	/// @Brief
	/// Draws all the shapes onto a given window
	/// </summary>
	/// <param name="t_window"> Window to draw them too </param>
	void draw(sf::RenderWindow* t_window);

	/// <summary>
	/// @Brief
	/// Allows the user to get the ID of a given shape by a pointer to the shape
	/// OR by giving it the body that the shape owns
	/// </summary>
	/// <param name="t_shape"> The shape you wish to get the ID of </param>
	/// <returns> The shape ID </returns>
	ShapeID getID(IShape* t_shape);
	ShapeID getID(b2Body* t_shape);

	b2Joint* createDistanceJoint(ShapeID, ShapeID);
	b2Joint* createDistanceJoint(IShape*, IShape*);

	b2Joint* createWheelJoint(ShapeID, ShapeID);
	b2Joint* createWheelJoint(IShape*, IShape*);

	void startWorld();

	void saveShapes(jsonf& t_data);
	void saveJoints(jsonf& t_data);

	void destroy(ShapeID t_id);
	void destroy(IShape* t_shape);
	void destroy(b2Body* t_body);
	void destroy(const IShape& t_other);

	/// <summary>
	/// @Brief
	/// Allows the user to remove all the shapes and delete everything created
	/// </summary>
	void reset();
private:

	ShapeManager();

	/// <summary>
	/// @Brief
	/// Destructor that will delete all the shapes that it is holding
	/// </summary>
	~ShapeManager();

	/// <summary>
	/// Function to remove similar code through the shapes
	/// Generates a body definition that all the shapes use
	/// </summary>
	/// <param name="pos"> position of the body </param>
	/// <returns> a body definition </returns>
	b2BodyDef generateBodyDef(Vector pos);

	std::vector<IShape*>::iterator destroyShape(IShape* t_shape);

	std::vector<IShape*> m_shapes;
	std::vector<b2Joint*> m_joints;

#ifdef BUILD_SRC

	sf::VertexArray m_jointsArray{ sf::Lines };
#endif

	b2World* m_world;
};

#include "shapeContactListener.h"

#endif