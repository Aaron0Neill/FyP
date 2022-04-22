#include "BulletPool.h"

BulletPool::BulletPool()
{
	m_manager = ShapeManager::getInstance();
	auto tm = TextureManager::getInstance();
	m_texture = tm->getTexture("Bullet");
}

//*************************************************************

void BulletPool::init(Vector t_pos, Vector t_velo)
{
	ShapeManager* manager = ShapeManager::getInstance();
	auto id = manager->createSprite("Bullet", t_pos);
	IShape* bullet = (*manager)[id];
	bullet->setTag("Bullet");
	bullet->setBodyType(b2_kinematicBody);
	bullet->getBody()->SetLinearVelocity(t_velo);
	bullet->getFixture()->SetSensor(true);
	float angle = t_velo.direction() * Rad2Deg;
	bullet->setRotation(angle);

	bullet->onTriggerEnter([manager, bullet](const IShape& t_other) {
		if (t_other.getTag() == "Enemy")
		{
			manager->destroy(t_other);
			manager->destroy(bullet);
		}
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
