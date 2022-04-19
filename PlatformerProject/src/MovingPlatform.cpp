#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(IShape* t_platform) : 
	m_body(t_platform)
{
	m_body->getBody()->SetLinearDamping(0);
	m_body->getBody()->SetLinearVelocity({ 5,0 });
}

//*************************************************************

void MovingPlatform::update(sf::Time t_dt)
{
	if (m_body->getWorldPos().x > 1500)
		m_body->getBody()->SetLinearVelocity({-5,0});
	else if (m_body->getWorldPos().x < 300)
		m_body->getBody()->SetLinearVelocity({5,0});
}
