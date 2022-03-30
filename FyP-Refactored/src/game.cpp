#include "Game.h"

Game::Game()
{
	m_world = WorldManager::getInstance();
	m_window = createWindow("SFML Basic");

	ContactListener* listener = new ContactListener(&m_shapes);
	m_world->getWorld()->SetContactListener(listener);

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

	auto floorID = m_shapes.createEdge({ 0,viewSize.y }, viewSize);

	auto triID = m_shapes.createPolygon(4, 0.5, { 250,250 });
	auto lWheel = m_shapes.createCircle(0.5, { 300,300 });
	auto rWheel = m_shapes.createCircle(0.5, { 200,300 });

	b2WheelJointDef lWheelDef;
	lWheelDef.Initialize(m_shapes[triID]->getBody(), m_shapes[lWheel]->getBody(), m_shapes[lWheel]->getBody()->GetPosition(), { 0,1 });
	lWheelDef.lowerTranslation = 0.01f;
	lWheelDef.upperTranslation = 0.05f;
	lWheelDef.enableLimit = true;

	b2WheelJointDef rWheelDef;
	rWheelDef.Initialize(m_shapes[triID]->getBody(), m_shapes[rWheel]->getBody(), m_shapes[rWheel]->getBody()->GetPosition(), { 0,1 });
	rWheelDef.lowerTranslation = 0.01f;
	rWheelDef.upperTranslation = 0.05f;
	rWheelDef.enableLimit = true;

	rWheelDef.motorSpeed = 1.f;
	rWheelDef.enableMotor = true;
	rWheelDef.maxMotorTorque = 5.f;


	m_world->getWorld()->CreateJoint(&lWheelDef);
	m_world->getWorld()->CreateJoint(&rWheelDef);
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