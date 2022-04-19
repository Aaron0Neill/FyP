#pragma once

#include "PolygonShape.h"

class Player
{
public:
	Player(IShape* t_body);

	void update(sf::Time t_dt);

	void jump();
private:
	void moveLeft(sf::Time t_dt);
	void moveRight(sf::Time t_dt);

	const float m_terminalVelocity;
	float m_incrementalVelocity;

	bool m_onGround;

	IShape* m_body;
};