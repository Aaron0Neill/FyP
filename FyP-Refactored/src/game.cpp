#include "Game.h"

Game::Game()
{
	m_world = WorldManager::getInstance();
	m_window = createWindow("SFML Basic");

	Vector viewSize{ 1920U , 1080U };
	sf::View view;
	view.setSize(viewSize);
	view.setCenter(viewSize / 2);
	m_window->setView(view);

	m_gui = GUIManager::getInstance();
	m_gui->init(m_window);

	m_builder = new ShapeEditor(m_window);
	m_builder->addShapeManager(&m_shapes);

	m_levelManager = new LevelLoader(&m_shapes);

	m_gui->addBuilder(m_builder);
	m_gui->addLevelLoader(m_levelManager);

	m_shapes.createEdge({ 0,viewSize.y }, viewSize);

	auto circID = m_shapes.createCircle(1.f, { 400,100 });
	m_shapes[circID]->setBodyType(b2BodyType::b2_staticBody);

}

//*************************************************************

Game::~Game()
{
	delete m_levelManager;
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
	static sf::Event e;
	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

		m_gui->handleEvent(e);

		m_builder->handleEvents(e);

		if (e.type == sf::Event::KeyPressed)
			if (e.key.code == sf::Keyboard::Tab)
			{
				m_world->startWorld();
				m_shapes.startWorld();
			}
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
	m_window->clear({215U,217U,215U, 255U});

	m_shapes.draw(m_window);

	m_builder->draw();

	m_gui->draw();

	m_window->display();
}

//*************************************************************

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), t_title);
}