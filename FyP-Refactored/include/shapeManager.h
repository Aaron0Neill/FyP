#ifndef SHAPE_MANAGER_INCLUDE
#define SHAPE_MANAGER_INCLUDE

#include <iostream>
#include <vector>

#include "box2d/b2_distance_joint.h"
#include "box2d/b2_wheel_joint.h"
#include "box2d/b2_world_callbacks.h"

#include "circleShape.h"
#include "json.hpp"
#include "polygonShape.h"
#include "TextureManager.h"
#include "vector.h"

class ContactListener;

using ShapeID = uint8;

class ShapeManager
{
public:
	/// <summary>
	/// @Brief
	/// Allows classes outside to get access to the static instance of the shapemanager 
	/// since the constructor is hidden, this is the only way to get it
	/// </summary>
	/// <returns> Returns a static instance of the shapes manager </returns>
	static ShapeManager* getInstance();

	/// <summary>
	/// @Brief
	/// Delete the copy constructor as this class is designed to only have 1 instance
	/// so we don't want any accidental or intentional copies
	/// </summary>
	ShapeManager(const ShapeManager&) = delete;
	void operator=(const ShapeManager&) = delete;

	/// <summary>
	/// @Brief
	/// The shape manager needs access to the world in order to create shapes etc....
	/// </summary>
	/// <param name="t_world"> Box2D world </param>
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

	/// <summary>
	/// @Brief 
	/// Creats a collider around the outside of the texture that is passed
	/// into it. The texture is pointed at so it needs to exist after the function is called
	/// ** Use texture manager where possible ** 
	/// </summary>
	/// <param name="t_texture">Texture to create a body around </param>
	/// <param name="t_centre"> Centre of the sprite </param>
	/// <returns> The ID of the shape </returns>
	ShapeID createSprite(Texture t_texture, Vector t_centre);

	/// <summary>
	/// @Brief 
	/// Attempts to load the texture from the texture manager by name passed
	/// if the texture is not loaded into the texture manager it will not work
	/// </summary>
	/// <param name="t_textureName"> Name of the texture it will try load </param>
	/// <param name="t_centre"> Centre of the sprite </param>
	/// <returns> the ID of a created shape or MAX ID if texture is not loaded</returns>
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
	/// Allows the user to search the shapes by tag
	/// </summary>
	/// <param name="t_tag"> tag name </param>
	/// <returns> First shape with the tag </returns>
	IShape* findByTag(const std::string& t_tag);

	/// <summary>
	/// @Brief
	/// Allows the user to get all the shapes
	/// </summary>
	/// <returns> Vector holding all the shapes</returns>
	std::vector<IShape*>& getShapes() { return m_shapes; }

	/// <summary>
	/// @Brief
	/// Allows other classes to access the joints
	/// </summary>
	/// <returns></returns>
	std::vector<b2Joint*> getJoints() const { return m_joints; }

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

	/// <summary>
	/// @Brief
	/// Overloaded getID to allow the user to get the ID of the shape based 
	/// on the body the shape has
	/// </summary>
	/// <param name="t_shape">The b2Body you want to find </param>
	/// <returns>The shape ID of that body </returns>
	ShapeID getID(b2Body* t_shape);

	/// <summary>
	/// @Brief
	/// Allows the user to programatically create a distance joint between 2 ID's
	/// </summary>
	/// <param name=""> The ID of the first shape </param>
	/// <param name=""> The ID of the second shape </param>
	/// <returns> The joint created </returns>
	b2Joint* createDistanceJoint(ShapeID, ShapeID);

	/// <summary>
	/// @Brief
	/// Overloaded Creation of the distance joint to accept 2 shape pointers 
	/// instead of the shape ID's
	/// </summary>
	/// <param name="">The first shape for the joint</param>
	/// <param name="">The second shape for the joint</param>
	/// <returns></returns>
	b2Joint* createDistanceJoint(IShape*, IShape*);

	b2Joint* createWheelJoint(ShapeID, ShapeID);
	b2Joint* createWheelJoint(IShape*, IShape*);

	/// <summary>
	/// @Brief
	/// Wakes all the b2body's that are inside the world
	/// </summary>
	void wakeShapes();

	/// <summary>
	/// @Brief
	/// Saves all the shape information into a json file
	/// </summary>
	/// <param name="t_data">File to save the info to</param>
	void saveShapes(jsonf& t_data);

	/// <summary>
	/// @Brief
	/// Saves all the joint information into a json file
	/// </summary>
	/// <param name="t_data">File to save joints to</param>
	void saveJoints(jsonf& t_data);

	/// <summary>
	/// @Brief
	/// Marks the shape at a given ID for destruction
	/// </summary>
	/// <param name="t_id">ID of the shape </param>
	void destroy(ShapeID t_id);

	/// <summary>
	/// @Brief
	/// Overload for the destruction to mark a specific shape for destruction
	/// </summary>
	/// <param name="t_shape">Shape you want to destroy </param>
	void destroy(IShape* t_shape);

	/// <summary>
	/// @Brief 
	/// Overload so you can pass a specific body you want to destroy
	/// </summary>
	/// <param name="t_body"> Body to destroy </param>
	void destroy(b2Body* t_body);

	/// <summary>
	/// @Brief
	/// Overload so you can mark collided objects for destruction
	/// </summary>
	/// <param name="t_other"> Object to destroy </param>
	void destroy(const IShape& t_other);

	/// <summary>
	/// @Brief
	/// Instantiates a copy of the shape given to it at the given position
	/// This can be very useful if you want to make a certain shape appear 
	/// multiple times
	/// </summary>
	/// <param name="t_shapeToCopy"> Template to copy from </param>
	/// <param name="t_copyPos"> Position to copy it to </param>
	/// <returns> The newly created shape </returns>
	IShape* instantiate(IShape& t_shapeToCopy, Vector t_copyPos = Vector());

	void clone(IShape& t_original, IShape& t_template);

	/// <summary>
	/// @Brief
	/// Allows the user to remove all the shapes and delete everything created
	/// </summary>
	void reset();
private:
	/// <summary>
	/// @brief
	/// Private Constructor so external classes can't instantiate the shape manager
	/// </summary>
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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_shape"></param>
	/// <returns></returns>
	b2FixtureDef generateFixtureDef(b2Shape* t_shape);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_original"></param>
	/// <param name="t_clone"></param>
	void cloneBodyDef(b2Body* t_original, b2BodyDef& t_clone);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_original"></param>
	/// <param name="t_clone"></param>
	void cloneFixtureDef(b2Fixture* t_original, b2FixtureDef& t_clone);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_shape"></param>
	/// <returns></returns>
	std::vector<IShape*>::iterator destroyShape(IShape* t_shape);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_shape"></param>
	/// <param name="t_pos"></param>
	/// <returns></returns>
	IShape* instantiateShape(IShape& t_shape, Vector t_pos);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_circle"></param>
	/// <param name="t_pos"></param>
	/// <returns></returns>
	IShape* instantiateCircle(IShape& t_circle, Vector t_pos);

	std::vector<IShape*> m_shapes;
	std::vector<b2Joint*> m_joints;
#ifdef BUILD_SRC
	sf::VertexArray m_jointsArray{ sf::Lines };
#endif

	b2World* m_world	{ nullptr };
};

#include "shapeContactListener.h"

#endif