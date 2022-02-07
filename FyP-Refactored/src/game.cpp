#include "Game.h"

void Game::run()
{
	m_world = WorldManager::getInstance();
	m_window = createWindow("SFML Basic");

	m_shapes.createPolygon(3, 1, {300,100});

	m_shapes.createCircle(0.5f, {250,0});
	m_shapes.createCircle(2, {125,0});

	m_shapes.createEdge({1, (float)WINDOW_HEIGHT - 10.0f}, { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT - 100.0f});
	m_shapes.createEdge({(float)WINDOW_WIDTH-1, 0}, { (float)WINDOW_WIDTH - 1, (float)WINDOW_HEIGHT});
	m_shapes.createEdge({ 1, 0 }, { 1,(float)WINDOW_HEIGHT });
	m_shapes.createEdge({100.f,300.0f}, { 500.0f , 500.0f});

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.0f);

	while (m_window->isOpen())
	{
		sf::Time dT = clock.restart();
		lag += dT;

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(dT);
		render();
	}
}

//*************************************************************

void Game::processEvents()
{
	static sf::Event e;
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

	}
}

//*************************************************************

void Game::update(sf::Time t_dTime)
{
	m_world->update(t_dTime);

	m_shapes.update();
}

//*************************************************************

void Game::render()
{
	m_window->clear();

	m_shapes.draw(m_window);

	m_window->display();
}

//*************************************************************

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title);
}
