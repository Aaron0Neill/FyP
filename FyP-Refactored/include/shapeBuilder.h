#ifndef SHAPE_BUILDER_INCLUDE
#define SHAPE_BUILDER_INCLUDE

#include <functional>
#include <unordered_map>

#include "createState.h"
#include "moveState.h"
#include "rotateState.h"
#include "scaleState.h"
#include "shapeManager.h"
#include "utils/vectorMaths.h"

enum class BuilderState : uint8
{
	CREATE,
	SELECT,
	SCALE,
	ROTATE, 
	MOVE
};

using State = std::shared_ptr<IBuildState>;
using StateFactory = std::unordered_map<BuilderState, std::function<State(sf::RenderWindow*, ShapeManager*)>>;

class ShapeBuilder
{
public:
	ShapeBuilder(sf::RenderWindow* t_window);
	~ShapeBuilder()=default;

	void setState(BuilderState);

	void handleEvents(sf::Event& t_event);

	void draw();

	inline void addShapeManager(ShapeManager* t_manager) { m_manager = t_manager; }

	State getState() { return m_currentState; }
private:

	template<typename T>
	void initFactory(BuilderState t_state)
	{
		m_factory.emplace(t_state, [](sf::RenderWindow* t_window, ShapeManager* t_manager) {
			return std::make_shared<T>(t_window, t_manager);
			});
	};

	State m_currentState;

	StateFactory m_factory;
	ShapeManager* m_manager;
	sf::RenderWindow* m_window;
};

#endif