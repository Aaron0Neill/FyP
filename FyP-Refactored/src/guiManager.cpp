#include "guiManager.h"

void GUIManager::init(sf::RenderWindow* t_window)
{
	m_gui = new tgui::Gui();
	m_gui->setWindow(*t_window);
	m_gui->setAbsoluteView({ 0,0,1920,1080 });
	initShapeBuild();
}

//*************************************************************

void GUIManager::handleEvent(sf::Event& e)
{
	m_gui->handleEvent(e);
}

//*************************************************************

void GUIManager::draw()
{
	m_gui->draw();
}

//*************************************************************

void GUIManager::initShapeBuild()
{
	tgui::Group::Ptr group;
	group = tgui::Group::create({ 400,1080 });
	group->setPosition({ 1920 - 400,0 });

	tgui::Panel::Ptr panel;
	panel = tgui::Panel::create();
	panel->setSize({ 400,1080 });
	panel->setWidgetName("ShapeBackground");
	panel->getRenderer()->setBackgroundColor(tgui::Color(109U,26U,54U));
	group->add(panel, "Panel");

	panel->onFocus([]() {std::cout << "Hover\n"; });
	
	tgui::Texture triangleTex("assets/images/Triangle.png");
	tgui::Texture squareTex("assets/images/Square.png");
	tgui::Texture pentagoTex("assets/images/Pentagon.png");
	tgui::Texture hexagonTex("assets/images/Hexagon.png");
	tgui::Texture septagonTex("assets/images/Septagon.png");
	tgui::Texture octagonTex("assets/images/Octagon.png");
	tgui::Texture circleTex("assets/images/Circle.png");
	
	int index = 0;
	std::vector<tgui::Picture::Ptr> pics;

	pics.push_back(tgui::Picture::create(triangleTex));
	pics[index]->setWidgetName("Triangle");
	pics[index++]->setPosition({ 25 , 25 });

	pics.push_back(tgui::Picture::create(squareTex));
	pics[index]->setWidgetName("Square");
	pics[index++]->setPosition({ 225, 25 });

	pics.push_back(tgui::Picture::create(pentagoTex));
	pics[index]->setWidgetName("Pentagon");
	pics[index++]->setPosition({ 25 ,225 });

	pics.push_back(tgui::Picture::create(hexagonTex));
	pics[index]->setWidgetName("Hexagon");
	pics[index++]->setPosition({ 225, 225 });

	pics.push_back(tgui::Picture::create(septagonTex));
	pics[index]->setWidgetName("Septagon");
	pics[index++]->setPosition({ 25,450 });

	pics.push_back(tgui::Picture::create(octagonTex));
	pics[index]->setWidgetName("Octagon");
	pics[index++]->setPosition({ 225,450 });


	auto circleptr = tgui::Picture::create(circleTex);
	circleptr->setWidgetName("Circle");
	circleptr->setPosition({ 25,675 });
	circleptr->onClick([this]() {});

	int i = 3;
	for (auto& ptr : pics)
	{
		
		ptr->onClick([this, i]() { this->m_builder->updatePoints(i); });

		group->add(ptr, ptr->getWidgetName());
		++i;
	}

	m_gui->add(group, "ImageGroup");
}
