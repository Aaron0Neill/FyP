#pragma once

#include "Enemy.h"
#include <array>

class EnemySpawner
{
public:
	EnemySpawner(IShape* t_shape);
	~EnemySpawner() = default;

	void update(sf::Time t_dt);

	void spawnLeft();

	void spawnRight();

private:
	PolygonShape m_template;
	ShapeManager* m_manager;

	bool m_spawnLeft{ false };
	bool m_spawnRight{ false };

	float m_spawnTimer;
	std::array<Vector, 5> m_spawnPositions;
};