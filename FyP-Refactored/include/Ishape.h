#ifndef I_SHAPE_INCLUDE
#define I_SHAPE_INCLUDE

#include "utils/ContactCallback.h"
#include "utils/json.hpp"
#include "utils/vector.h"
#include "TextureManager.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_joint.h>
#include <box2d/b2_distance_joint.h>
#include <SFML/Graphics/RenderWindow.hpp>

class IShape
{
public:
	virtual void update() = 0;

	virtual void draw(sf::RenderWindow* t_window) = 0;

	static void setDebugView(bool t_view) { m_debugView = t_view; }

	/// <summary>
	/// Get Functions
	/// </summary>
	inline virtual b2Fixture* getFixture()			{ return m_fixture; }
	inline virtual b2Body* getBody()				{ return m_body; }
	inline virtual sf::Vector2f getScale()	const	{ return m_scale; }
	inline virtual std::string getName()	const 	{ return m_name; }
	inline virtual std::string getTag()		const 	{ return m_tag; }
	inline virtual Vector getWorldPos()		const	{ return Vector(m_body->GetPosition()).fromWorldSpace(); }
	inline virtual bool getDestroyed()		const	{ return m_destroy; };
	inline virtual bool getVisible()		const	{ return m_visible; }


	/// <summary>
	/// Set Functions
	/// </summary>
	virtual void setPosition	(Vector t_pos);
	virtual void setXPosition	(float t_x);
	virtual void setYPosition	(float t_y);
	virtual void setRotation	(float t_rot);
	virtual void setScale		(float t_newScale)		=0;
	virtual void setXScale		(float t_newScale)		=0;
	virtual void setYScale		(float t_newScale)		=0;
	virtual void setBodyType	(b2BodyType t_type)		{ m_body->SetType(t_type); }
	virtual void setName		(std::string t_name)	{ m_name = t_name; }
	virtual void setTag			(std::string t_tag)		{ m_tag = t_tag; }
	virtual void setVisible		(bool t_visible)		{ m_visible = t_visible; }

	/// <summary>
	/// Conversion Functions
	/// </summary>
	virtual void toJson			(jsonf& t_json)			=0;
	virtual void fromJson		(jsonf& t_json)			=0;

	/// <summary>
	/// Callback function
	/// </summary>
	ContactCallback onCollisionEnter;
	ContactCallback onTriggerEnter;
	ContactCallback onCollisionExit;
	ContactCallback onTriggerExit;

protected:
	IShape()			= default;
	virtual ~IShape()	= default;
	friend class ShapeManager;

	std::string m_name;
	std::string m_tag;
	b2Body* m_body			{ nullptr };
	b2Fixture* m_fixture	{ nullptr };
	sf::Vector2f m_scale	{ 1.f, 1.f };
	mutable bool m_destroy	{ false };
	mutable bool m_visible	{ true };
	static bool m_debugView;
};

#endif