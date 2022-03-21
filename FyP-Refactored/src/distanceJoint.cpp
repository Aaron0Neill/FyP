#include "distanceJoint.h"

DistanceJointState::DistanceJointState(sf::RenderWindow* t_window, ShapeManager* t_manager) : 
	IBuildState(t_window, t_manager)
{
}

//*************************************************************

void DistanceJointState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f pos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			if (m_bodyA)
			{
				if (m_bodyB = m_manager->isMouseOnShape(pos))
					if (m_bodyA != m_bodyB)
					{
						m_manager->createDistanceJoint(m_bodyA, m_bodyB, 10.f);
						m_bodyA = nullptr;
						m_bodyB = nullptr;
					}
					else
						m_bodyB = nullptr;
			}
			else
				m_bodyA = m_manager->isMouseOnShape(pos);
		}
	}
}

//*************************************************************

void DistanceJointState::render()
{
}
