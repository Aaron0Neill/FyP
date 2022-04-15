#include "Platformer.h"	
#include <iostream>

PlatformScene::PlatformScene(sf::RenderWindow* t_window) : 
	IBaseScene(t_window)
{
	std::cout << "Platform Scene Created\n";

	//LevelLoader levelloader(&m_shapeManager);
	//
	//levelloader.loadLevel("../FyP-Refactored/assets/levels/PlatformTest.json");
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
	//m_shapeManager.update();
}

//*************************************************************

void PlatformScene::render()
{
	m_window->clear({200,215,200,255});

	//m_shapeManager.draw(m_window);

	m_window->display();
}
