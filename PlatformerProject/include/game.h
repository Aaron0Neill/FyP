#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include "globals.h"
#include "SceneManager.h"
#include "Platformer.h"
#include "MainMenu.h"

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

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

	SceneManager* m_sceneManager;
};

#endif