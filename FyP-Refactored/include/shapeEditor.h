#ifndef SHAPE_EDITOR_INCLUDE
#define SHAPE_EDITOR_INCLUDE

#include <functional>
#include <unordered_map>

#include "createState.h"
#include "distanceJoint.h"
#include "moveState.h"
#include "rotateState.h"
#include "scaleState.h"
#include "selectState.h"
#include "shapeManager.h"
#include "wheelJoint.h"
#include "utils/vectorMaths.h"

enum class EditState : uint8
{
	CREATE,
	SELECT,
	SCALE,
	ROTATE, 
	MOVE, 
	DISTANCE_JOINT,
	WHEEL_JOINT
};

class JointEditor;

using State = std::shared_ptr<IBuildState>;
using StateFactory = std::unordered_map<EditState, std::function<State(sf::RenderWindow*)>>;

class ShapeEditor
{
public:
	ShapeEditor(sf::RenderWindow* t_window);
	~ShapeEditor()=default;

	void setState(EditState);

	void handleEvents(sf::Event& t_event);

	void update();

	void draw();

	inline void addJointEditor(JointEditor* t_editor) { m_joints = t_editor; }

	State getState() { return m_currentState; }
	IShape* getCurrentShape() { return m_currentState->getSelected(); }
	JointEditor* getEditor() { return m_joints; }
private:

	template<typename T>
	void initFactory(EditState t_state)
	{
		m_factory.emplace(t_state, [](sf::RenderWindow* t_window) {
			return std::make_shared<T>(t_window);
			});
	};

	State m_currentState;

	JointEditor* m_joints;
	StateFactory m_factory;
	ShapeManager& m_manager;
	sf::RenderWindow* m_window;
};

#endif