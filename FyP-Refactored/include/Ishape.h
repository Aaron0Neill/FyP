#ifndef I_SHAPE_INCLUDE
#define I_SHAPE_INCLUDE

#include "utils/vector.h"

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
	inline virtual float getScale() { return m_scale; }

	inline virtual void setPosition(Vector t_pos)
	{
		float angle = m_body->GetAngle();
		m_body->SetTransform(t_pos.toWorldSpace(), angle);
	};

	virtual void setScale(float t_newScale) = 0;
	virtual void setRotation(float t_newRotation) = 0;
	virtual void setBodyType(b2BodyType t_type) { m_body->SetType(t_type); }

protected:
	IShape() = default;
	virtual ~IShape() = default;
	friend class ShapeManager;

	virtual void updateJoints()
	{
		if (!m_body->GetJointList())return;

		auto* joint = m_body->GetJointList();
		int iter = 0;
		while (joint)
		{
			if (iter >= m_joints.getVertexCount())
				m_joints.resize(iter + 2U);
			Vector currPos = joint->joint->GetAnchorA();
			Vector jointPos = joint->joint->GetAnchorB();

			m_joints[iter++].position = currPos.fromWorldSpace();
			m_joints[iter++].position = jointPos.fromWorldSpace();
			joint = joint->next;
		}
	}

	sf::VertexArray m_joints{sf::Lines};
	b2Body* m_body { nullptr };
	b2Fixture* m_fixture { nullptr };
	float m_scale { 1.f };
};

#endif