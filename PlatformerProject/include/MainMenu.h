#pragma once

#include "IBaseScene.h"

class MainMenu :
	public IBaseScene
{
public:
	MainMenu(sf::RenderWindow* t_window);
	~MainMenu() = default;

	void handleEvents()override;

	void update(sf::Time t_dt)override;

	void render()override;

private:
};