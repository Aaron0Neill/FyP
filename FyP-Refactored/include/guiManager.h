#ifndef GUI_MANAGER_INCLUDE
#define GUI_MANAGER_INCLUDE

#include <TGUI/AllWidgets.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TextureData.hpp>
#include <TGUI/Texture.hpp>
#include <TGUI/TextureManager.hpp>

#include "shapeEditor.h"
#include "levelLoader.h"

#include <iostream>

class GUIManager
{
public:
	/// <summary>
	/// Used to get the singleon instance of the GUI Manager
	/// </summary>
	/// <returns> Singleton Instance </returns>
	static GUIManager* getInstance()
	{
		static GUIManager instance;
		return &instance;
	}

	/// <summary>
	/// @Brief Function that will handle all the events around the gui
	/// Handles buttons / shortcut keys
	/// </summary>
	/// <param name="e"> Current event that's being processed </param>
	void handleEvent(sf::Event& e);

	/// <summary>
	/// @Brief Function to initialise the GUI manager 
	/// Inits the textures for the buttons and all the ui that will be used inside the project
	/// </summary>
	/// <param name="t_window"> Window that is used for rendering, used to set the view for the GUI </param>
	void init(sf::RenderWindow* t_window);

	/// <summary>
	/// @Brief Draws all the active elements inside the GUI
	/// </summary>
	void draw();

	/// <summary>
	/// Update all the parameters inside the select group to match the currently selected shape
	/// </summary>
	/// <param name="t_selectedShape"></param>
	void updateSelectedShape(IShape* t_selectedShape);

	/// <summary>
	/// Set Functions 
	/// </summary>
	void addBuilder(ShapeEditor* t_builder)		{ m_builder = t_builder; };
	void addLevelLoader(LevelLoader* t_loader)	{ m_loader = t_loader; }

	/// <summary>
	/// Get Functions
	/// </summary>
	ShapeEditor* getEditor()	{ return m_builder; }
	LevelLoader* getLoader()	{ return m_loader; }
	tgui::Gui* getGui()			{ return m_gui; }

private:
	GUIManager() = default;
	~GUIManager() = default;

	/// <summary>
	/// Init funcitons, these initialise the UI
	/// </summary>
	void initShapeBuild();
	void initSceneManagment();
	void initShapeEditor();
	void initTextures();
	void initJoint();


	tgui::Gui* m_gui			{ nullptr };
	ShapeEditor* m_builder		{ nullptr };
	LevelLoader* m_loader		{ nullptr };

	tgui::Texture* m_shapeTexture { nullptr };
	tgui::Texture* m_radioTexture { nullptr };

	tgui::RadioButton::Ptr m_buildButton	{ nullptr };
	tgui::RadioButton::Ptr m_editButton		{ nullptr };
	tgui::RadioButton::Ptr m_shapeButton	{ nullptr };
};

#endif