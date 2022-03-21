#ifndef I_BUILD_STATE_INCLUDE
#define I_BUILD_STATE_INCLUDE

#include "shapeManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

class IBuildState
{
public:
	IBuildState(sf::RenderWindow* t_window, ShapeManager* t_manager)
		: m_window(t_window), m_manager(t_manager) {}

	virtual ~IBuildState() = default;

	virtual void handleEvent(sf::Event& e) = 0;

	virtual void render() = 0;

	virtual IShape* getSelected() { return m_selectedShape; }

protected:
	sf::RenderWindow* m_window;
	ShapeManager* m_manager;
	static IShape* m_selectedShape;
};

#endif