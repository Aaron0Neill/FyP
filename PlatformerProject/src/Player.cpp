#include "Player.h"

Player::Player(IShape* t_body) :
	m_body(t_body), 
	m_terminalVelocity(7.5f),
	m_incrementalVelocity(60.f), 
	m_onGround(false)
{
	m_body->onCollisionEnter([this](const IShape& t_other) {
		if (t_other.getTag() == "Platform")
			m_onGround = true;
		});

	m_body->onCollisionExit([this](const IShape& t_other) {
		if (t_other.getTag() == "Platform")
			m_onGround = false;
		});
	m_body->getBody()->SetFixedRotation(true);
}

//*************************************************************

void Player::update(sf::Time t_dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveLeft(t_dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveRight(t_dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		jump();

	m_bullets.update(t_dt);
}

//*************************************************************

void Player::moveLeft(sf::Time t_dt)
{
	if (m_body->getBody()->GetLinearVelocity().x > -m_terminalVelocity)
		m_body->getBody()->ApplyLinearImpulseToCenter({ -m_incrementalVelocity * t_dt.asSeconds(), 0}, true);
}

//*************************************************************

void Player::moveRight(sf::Time t_dt)
{
	if (m_body->getBody()->GetLinearVelocity().x < m_terminalVelocity)
		m_body->getBody()->ApplyLinearImpulseToCenter({ m_incrementalVelocity * t_dt.asSeconds(), 0 }, true);
}

//*************************************************************

void Player::jump()
{
	if (m_onGround)
	{
		m_body->getBody()->ApplyLinearImpulseToCenter({ 0,-17.f * m_body->getBody()->GetMass()}, true);
		m_onGround = false;
	}
}

//*************************************************************

void Player::handleEvent(sf::Event& t_event, sf::RenderWindow* t_window)
{
	if (t_event.type == sf::Event::MouseButtonPressed)
	{
		Vector mousePos = t_window->mapPixelToCoords(sf::Mouse::getPosition(*t_window));
		Vector dir = mousePos - m_body->getWorldPos();
		dir /= dir.magnitude();
		m_bullets.init(m_body->getWorldPos(), dir * 25.f);
	}
}
