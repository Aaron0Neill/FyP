#pragma once

#include "utils/vector.h"
#include "shapeManager.h"
#include "Bullet.h"

class BulletPool
{
public:
	BulletPool();
	~BulletPool() = default;

	void init(Vector t_pos, Vector t_velo);

	void update(sf::Time t_dt);
private:
	void createTemplate();
	Texture m_texture;
	ShapeManager* m_manager;

	PolygonShape m_bulletTemplate;

	std::vector<Bullet> m_bullets;
	float m_bulletTimer{ 2.f };
};