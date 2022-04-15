#include "Game.h"

Game::Game()
{
	m_window = createWindow("Platformer Example");
	m_window->setKeyRepeatEnabled(false);

	sf::Vector2f viewSize{ 1920U , 1080U };
	sf::View view;
	view.setSize(viewSize);
	view.setCenter(viewSize.x / 2.f, viewSize.y / 2.f);
	m_window->setView(view);

	m_sceneManager = SceneManager::getInstance();
	m_sceneManager->setWindow(m_window);
	m_sceneManager->registerScene<PlatformScene>(SceneTypes::PLATFORM);
	m_sceneManager->registerScene<MainMenu>(SceneTypes::MAINMENU);
	m_sceneManager->setScene(SceneTypes::PLATFORM);
}

//*************************************************************

Game::~Game()
{
}

//*************************************************************

void Game::run()
{
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
	m_sceneManager->handleEvents();
}

//*************************************************************

void Game::update(sf::Time t_dTime)
{
	m_sceneManager->update(t_dTime);
}

//*************************************************************

void Game::render()
{
	m_sceneManager->render();
}

//*************************************************************

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title);
}