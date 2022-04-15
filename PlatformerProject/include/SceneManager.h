#pragma once

#include "IBaseScene.h"

#include <unordered_map>
#include <functional>
#include <memory>

enum class SceneTypes : uint8_t
{
	MAINMENU,
	PLATFORM
};

using Scene = std::unique_ptr<IBaseScene>;
using SceneFactory = std::unordered_map<SceneTypes, std::function<Scene(sf::RenderWindow*)>>;

class SceneManager
{
public:
	/// <summary>
	/// Function to allow outside classes to get the singleton instance of the Scenemanager
	/// </summary>
	/// <returns> Singleton Instance </returns>
	static SceneManager* getInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	/// <summary>
	/// Delete copy constructor and copy operator
	/// </summary>
	/// <param name="t_copy"> copy variable </param>
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	/// <summary>
	/// Function to register scene, this will bind the creation of class <T> 
	/// to the scenetype that it is matched with.
	/// So when you change scene the corresponding class will get created
	/// </summary>
	/// <typeparam name="T"> Class that will be created </typeparam>
	/// <param name="t_type"> Screen type the class is bound to </param>
	template<typename T>
	void registerScene(SceneTypes t_type)
	{
		m_factory[t_type] = [](sf::RenderWindow* t_window) {
			return std::make_unique<T>(t_window);
		};
	}

	/// <summary>
	/// Sets the window that the scenes will draw to
	/// </summary>
	/// <param name="t_window"> Target window for the scenens </param>
	void setWindow(sf::RenderWindow* t_window) { m_window = t_window; }

	/// <summary>
	/// Function that scenes can call to change the scenens
	/// </summary>
	/// <param name="t_type"> Screen type to change too </param>
	void setScene(SceneTypes t_type)
	{
		if (m_factory.count(t_type))
			m_currentScene = m_factory[t_type](m_window);
	}

	/// <summary>
	/// Calls the handle event function on the current scene
	/// </summary>
	void handleEvents() { m_currentScene->handleEvents(); };

	/// <summary>
	/// updates the current scene
	/// </summary>
	/// <param name="t_dt"> Time since the last frame update </param>
	void update(sf::Time t_dt) { m_currentScene->update(t_dt); };

	/// <summary>
	/// Renders the current scene
	/// </summary>
	void render() { m_currentScene->render(); };

private:
	/// <summary>
	/// Private constructor so no other classes can instanciate the SceneManager 
	/// </summary>
	SceneManager()
		: m_window{ nullptr } {};
	~SceneManager() = default;

	sf::RenderWindow* m_window;
	Scene m_currentScene;
	SceneFactory m_factory;
};