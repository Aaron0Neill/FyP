#include "Game.h"

Game::Game()
{
	m_world = WorldManager::getInstance();
	m_window = createWindow("SFML Basic");

	sf::Image icon;
	if (icon.loadFromFile("assets/images/icon.png"))
		m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	ContactListener* listener = new ContactListener(&m_shapes);
	m_world->getWorld()->SetContactListener(listener);

	Vector viewSize{ 1920U + 400U , 1080U }; // 1920 for level 400 for UI
	sf::View view;
	view.setSize(viewSize);
	view.setCenter(viewSize / 2);
	m_window->setView(view);

	m_gui = GUIManager::getInstance();
	m_gui->init(m_window);

	m_builder = new ShapeEditor(m_window);
	m_builder->addShapeManager(&m_shapes);

	m_jointEditor = new JointEditor(m_shapes, m_window);

	m_builder->addJointEditor(m_jointEditor);

	m_levelManager = new LevelLoader(&m_shapes);

	m_gui->addBuilder(m_builder);
	m_gui->addLevelLoader(m_levelManager);

	auto floorID = m_shapes.createEdge({ 0,viewSize.y }, viewSize);

	auto triID = m_shapes.createPolygon(4, 1, { 250,250 });
	auto lWheel = m_shapes.createCircle(.5, { 300,300 });
	auto rWheel = m_shapes.createCircle(.5, { 200,300 });
	
	m_shapes[triID]->setXScale(2);
	
	b2DistanceJointDef jDef;

	auto lwheelj = m_shapes.createWheelJoint(m_shapes[triID], m_shapes[lWheel]);
	auto rwheelj = m_shapes.createWheelJoint(m_shapes[triID], m_shapes[rWheel]);
	
	static_cast<b2WheelJoint*>(lwheelj)->EnableLimit(true);
	std::cout << "Lower: " << static_cast<b2WheelJoint*>(lwheelj)->GetLowerLimit() << ", upper : " << static_cast<b2WheelJoint*>(lwheelj)->GetUpperLimit() << std::endl;
	static_cast<b2WheelJoint*>(lwheelj)->SetLimits(-1.f, 1.f);

	static_cast<b2WheelJoint*>(rwheelj)->EnableLimit(true);
	static_cast<b2WheelJoint*>(rwheelj)->SetLimits(-1.f,1.f);
	static_cast<b2WheelJoint*>(rwheelj)->EnableMotor(true);
	static_cast<b2WheelJoint*>(rwheelj)->SetMaxMotorTorque(10.f);
	static_cast<b2WheelJoint*>(rwheelj)->SetMotorSpeed(5.f);

	static_cast<b2WheelJoint*>(rwheelj)->SetStiffness(0.5);
	static_cast<b2WheelJoint*>(lwheelj)->SetStiffness(0.5);
	
	auto square = m_shapes.createPolygon(4, 2, { 100,400 });
	m_shapes[square]->setBodyType(b2_staticBody);
	m_shapes[square]->getFixture()->SetSensor(true);


	auto lSquare = m_shapes.createPolygon(4, 2, { 400,400 });
	auto rSquare = m_shapes.createPolygon(4, 2, { 800,400 });

	m_testJoint = static_cast<b2DistanceJoint*>(m_shapes.createDistanceJoint(lSquare, rSquare));

	m_testJoint->SetMaxLength(1);
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

	m_builder->update();

	m_jointEditor->update();
}

//*************************************************************

void Game::render()
{
	m_window->clear({215U,217U,215U, 255U});

	m_shapes.draw(m_window);

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