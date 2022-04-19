#include "Player.h"

Player::Player(IShape* t_body) :
	m_body(t_body), 
	m_terminalVelocity(5.f),
	m_incrementalVelocity(60.f), 
	m_onGround(false)
{
	m_body->setName("Player");

	m_body->onCollisionEnter([this](const IShape& t_other) {
		m_onGround = true;
		});

	m_body->onCollisionExit([this](const IShape& t_other) {
		m_onGround = false;
		});

	m_body->getBody()->SetFixedRotation(true);
}

//*************************************************************

void Player::update(sf::Time t_dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft(t_dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight(t_dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump();
}

//*************************************************************

void Player::moveLeft(sf::Time t_dt)
{
	if (m_body->getBody()->GetLinearVelocity().x > -m_terminalVelocity && m_onGround)
		m_body->getBody()->ApplyLinearImpulseToCenter({ -m_incrementalVelocity * t_dt.asSeconds(), 0}, true);
}

//*************************************************************

void Player::moveRight(sf::Time t_dt)
{
	if (m_body->getBody()->GetLinearVelocity().x < m_terminalVelocity && m_onGround)
		m_body->getBody()->ApplyLinearImpulseToCenter({ m_incrementalVelocity * t_dt.asSeconds(), 0 }, true);
}

//*************************************************************

void Player::jump()
{
	if (m_onGround)
	{
		m_body->getBody()->ApplyLinearImpulseToCenter({ 0,-20.f * m_body->getBody()->GetMass()}, true);
		m_onGround = false;
	}
}
