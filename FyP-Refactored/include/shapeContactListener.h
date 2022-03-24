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
	ContactListener(ShapeManager* t_manager) : m_manager(t_manager) {};
	~ContactListener() = default;

	virtual void BeginContact(b2Contact* t_contact)override
	{
		ShapeID id1 = m_manager->getID(t_contact->GetFixtureA()->GetBody());
		ShapeID id2 = m_manager->getID(t_contact->GetFixtureB()->GetBody());
		std::cout << "Shape: " << (int)id1 << " begun colliding with shape: " << (int)id2 << std::endl;
	}
private:
	ShapeManager* m_manager;
};


#endif