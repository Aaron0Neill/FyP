#pragma once

#include "Ishape.h"

class MovingPlatform
{
public:
	MovingPlatform(IShape* t_platform);

	void update(sf::Time t_dt);

private:
	IShape* m_body; 
};