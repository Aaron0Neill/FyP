#pragma once

#include "IBaseScene.h"
#include "shapeManager.h"
#include "utils/levelLoader.h"

#include "Player.h"
#include "MovingPlatform.h"

class PlatformScene : 
	public IBaseScene
{
public:
	PlatformScene(sf::RenderWindow* t_window);
	~PlatformScene() = default;

	/// <summary>
	/// 
	/// </summary>
	void handleEvents()			override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_dt"></param>
	void update(sf::Time t_dt)	override;

	/// <summary>
	/// 
	/// </summary>
	void render()				override;

private:
	ShapeManager* m_shapeManager	{ nullptr };
	b2World* m_world				{ nullptr };

	Player* m_player				{ nullptr };
	MovingPlatform* m_body		{ nullptr };

	uint8 m_velocityIterations		{ 6 };
	uint8 m_positionIterations		{ 2 };
};