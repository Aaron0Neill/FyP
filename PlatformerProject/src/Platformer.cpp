#include "Platformer.h"	
#include <iostream>

PlatformScene::PlatformScene(sf::RenderWindow* t_window) :
	IBaseScene(t_window)
{
	m_world = new b2World({ 0,9.8f });
	m_shapeManager = ShapeManager::getInstance();
	m_shapeManager->setWorld(m_world);

	auto tm = TextureManager::getInstance();
	tm->loadTexture("Bullet", "assets/textures/bullet.png");

	LevelLoader levelloader;
	levelloader.loadLevel("../FyP-Refactored/assets/levels/Platform.json");

	(*m_shapeManager)[0]->setTag("Platform");


	IShape* playerShape = m_shapeManager->find("Player");
	m_player = new Player(playerShape);

	IShape* pf = m_shapeManager->find("Mover");
	m_body = new MovingPlatform(pf);

	IShape* enemy = m_shapeManager->findByTag("Enemy");
	m_spawner = new EnemySpawner(enemy);
}

PlatformScene::~PlatformScene()
{
	delete m_player;
	delete m_body; 
	delete m_spawner;
}

//*************************************************************

void PlatformScene::handleEvents()
{
	static sf::Event e;
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

		m_player->handleEvent(e, m_window);
	}
}

//*************************************************************

void PlatformScene::update(sf::Time t_dt)
{
	m_world->Step(t_dt.asSeconds(), m_velocityIterations, m_positionIterations);
	m_shapeManager->update();

	m_player->update(t_dt);

	m_body->update(t_dt);

	m_spawner->update(t_dt);
}

//*************************************************************

void PlatformScene::render()
{
	m_window->clear({200,215,200,255});

	m_shapeManager->draw(m_window);

	m_window->display();
}
