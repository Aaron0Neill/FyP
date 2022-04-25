#ifndef SHAPE_CONTACT_LISTENER_H
#define SHAPE_CONTACT_LISTENER_H

#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_contact.h"
#include "shapeManager.h"

#include <iostream>

class ContactListener : 
	public b2ContactListener
{
public:
	ContactListener() : m_manager(*ShapeManager::getInstance()) { };
	~ContactListener() = default;

	/// <summary>
	/// Function that gets called when 2 bodies start colliding
	/// </summary>
	/// <param name="t_contact"></param>
	virtual void BeginContact(b2Contact* t_contact)override
	{
		ShapeID id1 = m_manager.getID(t_contact->GetFixtureA()->GetBody());
		ShapeID id2 = m_manager.getID(t_contact->GetFixtureB()->GetBody());

		constexpr ShapeID NULL_ID = std::numeric_limits<ShapeID>::max();

		if (id1 == NULL_ID || id2 == NULL_ID) return;
		
		auto* bodyA = m_manager[id1];
		auto* bodyB = m_manager[id2];

		(bodyA->getFixture()->IsSensor()) ? 
			bodyA->onTriggerEnter(*bodyB) :
			bodyA->onCollisionEnter(*bodyB);

		(bodyB->getFixture()->IsSensor()) ? 
			bodyB->onTriggerEnter(*bodyA) :
			bodyB->onCollisionEnter(*bodyA);
	}

	/// <summary>
	/// Function that gets called when 2 bodies stop colliding 
	/// </summary>
	/// <param name="t_contact"></param>
	virtual void EndContact(b2Contact* t_contact)override
	{
		ShapeID id1 = m_manager.getID(t_contact->GetFixtureA()->GetBody());
		ShapeID id2 = m_manager.getID(t_contact->GetFixtureB()->GetBody());

		constexpr ShapeID NULL_ID = std::numeric_limits<ShapeID>::max();

		if (id1 == NULL_ID || id2 == NULL_ID) return;

		auto* bodyA = m_manager[id1];
		auto* bodyB = m_manager[id2];

		(bodyA->getFixture()->IsSensor()) ?
			bodyA->onTriggerExit(*bodyB) :
			bodyA->onCollisionExit(*bodyB);

		(bodyB->getFixture()->IsSensor()) ?
			bodyB->onTriggerExit(*bodyA) :
			bodyB->onCollisionExit(*bodyA);
	}
private:
	ShapeManager& m_manager;
};


#endif