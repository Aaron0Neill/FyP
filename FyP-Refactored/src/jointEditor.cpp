#ifdef BUILD_SRC
#include "jointEditor.h"

JointEditor::JointEditor(sf::RenderWindow* t_window) :
	m_manager(*ShapeManager::getInstance()), m_window(t_window)
{
	float radius = 15.f;
	m_template.setRadius(radius);
	m_template.setOutlineThickness(-1.f);
	m_template.setFillColor(sf::Color::Transparent);
	m_template.setOutlineColor(sf::Color::White);
	m_template.setOrigin(radius, radius);
}

//*************************************************************

void JointEditor::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		Vector mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
	
		for (auto& circ : m_joints)
		{
			Vector pos = circ.getPosition();
			float sqrRad = circ.getRadius() * circ.getRadius();

			if (vectorLengthSquared(mousePos - pos) < sqrRad)
			{
				// give joint to gui manager 
				// activate joint modifier
				size_t index = &circ - &m_joints[0];
				
				GUIManager* gui = GUIManager::getInstance();

				m_selectedJoint = m_manager.getJoints()[index];

				gui->updateSelectedJoint(m_selectedJoint);
				break;
			}
		}
	}
}

//*************************************************************

void JointEditor::update()
{
	size_t size = m_manager.getJoints().size();
	for (size_t i = 0; i < size; ++i)
	{
		if (i >= m_joints.size())
			m_joints.push_back(m_template);

		b2Joint* currJoint = m_manager.getJoints()[i];

		Vector cp = currJoint->GetAnchorA() + currJoint->GetAnchorB();
		cp /= 2;

		m_joints[i].setPosition(cp.fromWorldSpace());
	}
}

//*************************************************************

void JointEditor::draw()
{
	for (auto& circ : m_joints)
		m_window->draw(circ);
}

#endif