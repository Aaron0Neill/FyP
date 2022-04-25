#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(IShape* t_shape) : 
	m_spawnTimer(0)
{
	m_manager = ShapeManager::getInstance();
	m_manager->clone(*t_shape, m_template);
	m_manager->destroy(t_shape);
	m_template.getBody()->SetFixedRotation(true);

	m_manager->find("LeftSpawner")->onTriggerEnter([this](const IShape& t_other) {
		m_spawnLeft = (t_other.getName() == "Player");
		});

	m_manager->find("RightSpawner")->onTriggerEnter([this](const IShape& t_other) {
		m_spawnRight = (t_other.getName() == "Player");
		});

	m_spawnPositions[0] = { 100 ,100 }; // TL
	m_spawnPositions[1] = { 1750,100 }; // TR
	m_spawnPositions[2] = { 960 ,300}; // MIDDLE
	m_spawnPositions[3] = { 100,700}; // BL 
	m_spawnPositions[4] = { 1750,700}; // BR
}

//*************************************************************

void EnemySpawner::update(sf::Time t_dt)
{
	if (m_spawnLeft)
		spawnLeft();

	if (m_spawnRight)
		spawnRight();
}

//*************************************************************

void EnemySpawner::spawnLeft()
{
	auto topShape = m_manager->instantiate(m_template);
	topShape->setPosition(m_spawnPositions[0]);
	topShape->getBody()->SetAwake(true);

	auto bottomShape = m_manager->instantiate(m_template);
	bottomShape->setPosition(m_spawnPositions[3]);
	bottomShape->getBody()->SetAwake(true);

	m_spawnLeft = false;
}

//*************************************************************

void EnemySpawner::spawnRight()
{
	auto topShape = m_manager->instantiate(m_template);
	topShape->setPosition(m_spawnPositions[1]);
	topShape->getBody()->SetAwake(true);

	auto bottomShape = m_manager->instantiate(m_template);
	bottomShape->setPosition(m_spawnPositions[4]);
	bottomShape->getBody()->SetAwake(true);

	m_spawnRight = false;
}
