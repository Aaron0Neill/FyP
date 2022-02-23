#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>
#include <globals.h>

#include <shapeManager.h>
#include <ShapeBuilder.h>
#include <worldManager.h>

#include <box2d/b2_distance_joint.h>
#include <box2d/b2_revolute_joint.h>
#include <box2d/b2_wheel_joint.h>
#include <box2d/b2_pulley_joint.h>
#include <box2d/b2_prismatic_joint.h>

#include <guiManager.h>

class Game
{
public:
	Game();
	~Game() = default;

	/// <summary>
	/// Initializes and starts the game loop
	/// </summary>
	void run();

	/// <summary>
	/// Handles system events (input, etc.)
	/// </summary>
	void processEvents();

	/// <summary>
	/// Called once every game tick
	/// </summary>
	/// <param name="t_dTime">Time in seconds since the last update</param>
	void update(sf::Time t_dTime);

	/// <summary>
	/// Clears, redraws and displays the framebuffer
	/// </summary>
	void render();

private:

	/// <summary>
	/// Creates an sf::RenderWindow on the stack
	/// </summary>
	/// <param name="t_title">Title for the sf::RenderWindow</param>
	/// <returns>A pointer to a stack-allocated sf::RenderWindow</returns>
	sf::RenderWindow* createWindow(std::string t_title);
	sf::RenderWindow* m_window{ nullptr };

	ShapeManager m_shapes;

	WorldManager* m_world { nullptr };

	ShapeBuilder* m_builder;

	GUIManager* m_gui;
};

#endif