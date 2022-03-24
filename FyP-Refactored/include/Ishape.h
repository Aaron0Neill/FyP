#ifndef I_SHAPE_INCLUDE
#define I_SHAPE_INCLUDE

#include "utils/vector.h"
#include "utils/json.hpp"

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

	inline virtual b2Fixture* getFixture() { return m_fixture; }
	inline virtual b2Body* getBody() { return m_body; }
	inline virtual sf::Vector2f getScale() { return m_scale; }

	inline virtual void setPosition(Vector t_pos)
	{
		float angle = m_body->GetAngle();
		m_body->SetTransform(t_pos.toWorldSpace(), angle);
	};

	inline virtual void setXPosition(float t_x)
	{
		Vector pos = m_body->GetPosition();
		pos = pos.fromWorldSpace();
		pos.x = t_x;
		setPosition(pos);
	}

	inline virtual void setYPosition(float t_y)
	{
		Vector pos = m_body->GetPosition();
		pos = pos.fromWorldSpace();
		pos.y = t_y;
		setPosition(pos);
	}

	inline virtual void setRotation(float t_rot)
	{
		Vector pos = m_body->GetPosition();
		m_body->SetTransform(pos, t_rot * Deg2Rad);
	}

	virtual void setScale(float t_newScale) = 0;
	virtual void setXScale(float t_newScale) = 0;
	virtual void setYScale(float t_newScale) = 0;
	virtual void setBodyType(b2BodyType t_type) { m_body->SetType(t_type); }

	virtual void toJson(jsonf& t_json) = 0;
	virtual void fromJson(jsonf& t_json) = 0;

protected:
	IShape() = default;
	virtual ~IShape() = default;
	friend class ShapeManager;

	b2Body* m_body { nullptr };
	b2Fixture* m_fixture { nullptr };
	sf::Vector2f m_scale {1.f, 1.f};
};

#endif