#ifndef WORLD_MANAGER_INCLUDE
#define WORLD_MANAGER_INCLUDE

#include <box2d/b2_world.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class WorldManager
{
public:
	static WorldManager* getInstance()
	{
		static WorldManager instance;

		return &instance;
	};

	void update(sf::Time t_dt) 
	{
		m_world->Step(t_dt.asSeconds(), m_velocityIterations, m_positionIterations);
	};
	
	void wakeShapes() { m_world->SetGravity({ 0,9.8f }); }

	b2World* operator->() { return m_world; }

	b2World* getWorld() { return m_world; }
private:
	WorldManager() 
	{
		b2Vec2 gravity{ 0,0.0f };
		m_world = new b2World(gravity);
	}

	~WorldManager()
	{
		delete m_world;
	}

	b2World* m_world			{ nullptr };
	uint8 m_velocityIterations	{ 6 };
	uint8 m_positionIterations	{ 2 };
};

#endif