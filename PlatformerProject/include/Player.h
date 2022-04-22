#pragma once

#include "shapeManager.h"
#include "BulletPool.h"

class Player
{
public:
	Player(IShape* t_body);

	void update(sf::Time t_dt);

	void jump();

	void handleEvent(sf::Event& t_event, sf::RenderWindow* t_window);
private:
	void moveLeft(sf::Time t_dt);
	void moveRight(sf::Time t_dt);

	BulletPool m_bullets;

	const float m_terminalVelocity;
	float m_incrementalVelocity;

	bool m_onGround;

	IShape* m_body;
};