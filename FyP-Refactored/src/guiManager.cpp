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

void GUIManager::draw()
{
	m_gui->draw();
}

void GUIManager::initShapeBuild()
{
	tgui::Group::Ptr group;
	group = tgui::Group::create({ 400,1080 });
	group->setPosition({ 1920 - 400,0 });
	
	tgui::Texture triangleTex("assets/images/Triangle.png");
	tgui::Texture squareTex("assets/images/Square.png");
	tgui::Texture pentagoTex("assets/images/Pentagon.png");
	tgui::Texture hexagonTex("assets/images/Hexagon.png");
	tgui::Texture septagonTex("assets/images/Septagon.png");
	tgui::Texture octagonTex("assets/images/Octagon.png");
	
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
	pics[index++]->setPosition({ 25 ,250 });

	pics.push_back(tgui::Picture::create(hexagonTex));
	pics[index]->setWidgetName("Hexagon");
	pics[index++]->setPosition({ 225, 250 });

	pics.push_back(tgui::Picture::create(septagonTex));
	pics[index]->setWidgetName("Septagon");
	pics[index++]->setPosition({ 25,500 });

	pics.push_back(tgui::Picture::create(octagonTex));
	pics[index]->setWidgetName("Octagon");
	pics[index++]->setPosition({ 225,500 });

	for (auto& ptr : pics)
	{
		ptr->onClick([ptr]() {std::cout << ptr->getWidgetName() << std::endl; });
		group->add(ptr, ptr->getWidgetName());
	}

	m_gui->add(group, "ImageGroup");
	//m_gui->add(picPtr, "Triangle");
}
