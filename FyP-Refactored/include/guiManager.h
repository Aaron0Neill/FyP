#ifndef GUI_MANAGER_INCLUDE
#define GUI_MANAGER_INCLUDE

#include <TGUI/AllWidgets.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TextureData.hpp>
#include <TGUI/Texture.hpp>
#include <TGUI/TextureManager.hpp>

#include <iostream>

class GUIManager
{
public:
	static GUIManager* getInstance()
	{
		static GUIManager instance;
		return &instance;
	}

	void handleEvent(sf::Event& e);

	void init(sf::RenderWindow* t_window);

	void draw();

private:
	GUIManager() = default;
	~GUIManager() = default;

	void initShapeBuild();

	tgui::Gui* m_gui;
		
};

#endif