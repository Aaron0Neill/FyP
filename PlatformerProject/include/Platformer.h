#pragma once

#include "IBaseScene.h"
//#include "shapeManager.h"
//#include "utils/levelLoader.h"

class PlatformScene : 
	public IBaseScene
{
public:
	PlatformScene(sf::RenderWindow* t_window);
	~PlatformScene() = default;

	void handleEvents()override;

	void update(sf::Time t_dt)override;

	void render()override;

private:
	//ShapeManager m_shapeManager;
};