#pragma once
#ifdef BUILD_SRC

#include "shapeManager.h"
#include "guiManager.h"
#include "vectorMaths.h"

class JointEditor
{
public:
	JointEditor(ShapeManager& t_manager, sf::RenderWindow* t_window);
	~JointEditor() = default;

	void handleEvent(sf::Event& e);

	void update();

	void draw();

	b2Joint* getCurrentJoint() { return m_selectedJoint; }

private:
	std::vector<sf::CircleShape> m_joints;
	ShapeManager& m_manager;
	sf::RenderWindow* m_window;
	sf::CircleShape m_template;
	b2Joint* m_selectedJoint	{ nullptr };
};
#endif