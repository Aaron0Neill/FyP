#ifndef I_BUILD_STATE_INCLUDE
#define I_BUILD_STATE_INCLUDE

#include "shapeManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

class IBuildState
{
public:
	IBuildState(sf::RenderWindow* t_window)
		: m_window(t_window), m_manager(ShapeManager::getInstance()) {}

	virtual ~IBuildState() = default;
	virtual void handleEvent(sf::Event& e) = 0;
	virtual void render() = 0;
	virtual void update() {};

	/// <summary>
	/// Allows other classes to get the currently selected shape 
	/// </summary>
	/// <returns> Currently selected shape </returns>
	virtual IShape* getSelected() { return m_selectedShape; }

	/// <summary>
	/// Allows other classes to access the most recently selected joint
	/// </summary>
	/// <returns> The most recently selected joint </returns>
	virtual b2Joint* getSelectedJoint() { return m_selectedJoint; }

protected:
	sf::RenderWindow* m_window;
	ShapeManager* m_manager;
	static IShape* m_selectedShape;
	static b2Joint* m_selectedJoint; 
};

#endif