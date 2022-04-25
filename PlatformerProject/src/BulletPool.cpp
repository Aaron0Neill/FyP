#include "BulletPool.h"

BulletPool::BulletPool()
{
	m_manager = ShapeManager::getInstance();
	auto tm = TextureManager::getInstance();
	m_texture = tm->getTexture("Bullet");

	createTemplate();
}

//*************************************************************

void BulletPool::init(Vector t_pos, Vector t_velo)
{
	float angle = t_velo.direction() * Rad2Deg;
	auto bullet = m_manager->instantiate(m_bulletTemplate);

	bullet->setPosition(t_pos);
	bullet->getBody()->SetLinearVelocity(t_velo);
	bullet->setRotation(angle);

	bullet->onTriggerEnter([this, bullet](const IShape& t_other) {
		if (t_other.getTag() == "Enemy")
		{
			m_manager->destroy(bullet);
			m_manager->destroy(t_other);
		}
		else if (t_other.getTag() == "Platform")
			m_manager->destroy(bullet);
		});
	
	m_bullets.push_back({ bullet, m_bulletTimer });
}

//*************************************************************

void BulletPool::update(sf::Time t_dt)
{
	for (auto& bullet : m_bullets)
	{
		bullet.timer -= t_dt.asSeconds();
		if (bullet.timer <= 0)
		{
			m_manager->destroy(bullet.shape);
			int index = &bullet - &m_bullets[0];
			m_bullets.erase(m_bullets.begin() + index);
		}
	}
}

//*************************************************************

void BulletPool::createTemplate()
{
	IShape* bullet = m_manager->findByTag("Bullet");

	if (bullet)
	{
		m_manager->clone(*bullet, m_bulletTemplate);

		m_manager->destroy(bullet);
	}
}
