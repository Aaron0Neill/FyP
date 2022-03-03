#ifndef GUI_MANAGER_INCLUDE
#define GUI_MANAGER_INCLUDE

#include <TGUI/AllWidgets.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TextureData.hpp>
#include <TGUI/Texture.hpp>
#include <TGUI/TextureManager.hpp>

#include "shapeBuilder.h"

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

	void addBuilder(ShapeBuilder* t_builder) { m_builder = t_builder; };
	ShapeBuilder* getBuilder() { return m_builder; }

	void showFolder();

private:
	GUIManager() = default;
	~GUIManager() = default;

	void initShapeBuild();
	void initSceneManagment();


	tgui::Gui* m_gui;
	ShapeBuilder* m_builder;
	tgui::RadioButton::Ptr m_buildButton { nullptr };
	tgui::RadioButton::Ptr m_editButton { nullptr };
	tgui::RadioButton::Ptr m_shapeButton { nullptr };
};

#endif