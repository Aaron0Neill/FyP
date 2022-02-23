#ifndef I_BUILD_STATE_INCLUDE
#define I_BUILD_STATE_INCLUDE

#include <SFML/Graphics/RenderWindow.hpp>

class IBuildState
{
public:
	IBuildState(sf::RenderWindow* t_window)
		: m_window(t_window) {}

	virtual ~IBuildState() = default;

	virtual void handleEvent(sf::Event& e) = 0;

	virtual void update() = 0;

	virtual void redner() = 0;

protected:
	sf::RenderWindow* m_window;
};

#endif