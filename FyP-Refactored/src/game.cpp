#include "Game.h"

Game::Game()
{
	m_world = WorldManager::getInstance();
	m_window = createWindow("SFML Basic");

	m_shapes = ShapeManager::getInstance();
	m_shapes->setWorld(m_world->getWorld());

	sf::Image icon;
	if (icon.loadFromFile("assets/images/icon.png"))
		m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Vector viewSize{ 1920U + 400U , 1080U }; // 1920 for level 400 for UI
	sf::View view;
	view.setSize(viewSize);
	view.setCenter(viewSize / 2);
	m_window->setView(view);

	m_gui = GUIManager::getInstance();
	m_gui->init(m_window);

	m_builder = new ShapeEditor(m_window);

	m_jointEditor = new JointEditor(m_window);

	m_builder->addJointEditor(m_jointEditor);

	m_levelManager = new LevelLoader();

	m_gui->addBuilder(m_builder);
	m_gui->addLevelLoader(m_levelManager);
	
	auto floorID = m_shapes->createEdge({ 0,viewSize.y }, viewSize);


	//auto hinge = m_shapes->createPolygon(4, 0.5, { 400,400 });
	//(*m_shapes)[hinge]->setBodyType(b2_staticBody);
	//
	//auto pf = m_shapes->createPolygon(4, 0.5, { 400,400 });
	//(*m_shapes)[pf]->setXScale(20);
	//(*m_shapes)[pf]->getBody()->SetGravityScale(0);
	//
	//b2RevoluteJointDef rev;
	//rev.Initialize((*m_shapes)[pf]->getBody(), (*m_shapes)[hinge]->getBody(), (*m_shapes)[hinge]->getBody()->GetPosition());
	//
	//rev.enableMotor = true;
	//rev.maxMotorTorque = 120;
	//rev.motorSpeed = 0;
	//
	//m_revJoint = static_cast<b2RevoluteJoint*>(m_world->getWorld()->CreateJoint(&rev));
}

//*************************************************************

Game::~Game()
{
	delete m_levelManager;
	delete m_jointEditor;
	delete m_builder;
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

		m_jointEditor->handleEvent(e);

		if (e.type == sf::Event::KeyPressed)
			if (e.key.code == sf::Keyboard::Q)
			{
				m_world->startWorld();
				m_shapes->startWorld();
			}
			else if (e.key.code == sf::Keyboard::Tilde)
				m_shapes->reset();
	}
}

//*************************************************************

void Game::update(sf::Time t_dTime)
{
	m_world->update(t_dTime);

	m_shapes->update();

	m_builder->update();

	m_jointEditor->update();

	//m_revJoint->SetMotorSpeed(m_revJoint->GetJointAngle() * -0.1);
}

//*************************************************************

void Game::render()
{
	m_window->clear({215U,217U,215U, 255U});

	m_shapes->draw(m_window);

	m_builder->draw();

	m_gui->draw();

	m_jointEditor->draw();

	m_window->display();
}

//*************************************************************

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH + 400U, WINDOW_HEIGHT), t_title);
}