#include "Platformer.h"	
#include <iostream>

PlatformScene::PlatformScene(sf::RenderWindow* t_window) :
	IBaseScene(t_window)
{
	m_world = new b2World({ 0,9.8f });
	m_shapeManager = new ShapeManager(m_world);

	LevelLoader levelloader(m_shapeManager);

	levelloader.loadLevel("../FyP-Refactored/assets/levels/Platform.json");

	m_player = new Player(m_shapeManager->find("Player"));

	m_body = new MovingPlatform(m_shapeManager->find("Platform"));
}

//*************************************************************

void PlatformScene::handleEvents()
{
	static sf::Event e;
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();
	}
}

//*************************************************************

void PlatformScene::update(sf::Time t_dt)
{
	m_world->Step(t_dt.asSeconds(), m_velocityIterations, m_positionIterations);
	m_shapeManager->update();

	m_player->update(t_dt);

	m_body->update(t_dt);
}

//*************************************************************

void PlatformScene::render()
{
	m_window->clear({200,215,200,255});

	m_shapeManager->draw(m_window);

	m_window->display();
}
