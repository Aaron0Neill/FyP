#ifndef LEVEL_LOADER_INCLUDE
#define LEVEL_LOADER_INCLUDE

#include "shapeManager.h"
#include "json.hpp"
#include <fstream>

class LevelLoader
{
public:
	LevelLoader() :
		m_managerPtr(ShapeManager::getInstance()), m_path("assets/textures") {};
	~LevelLoader()=default;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_levelPath"></param>
	void saveLevel(const std::string& t_levelPath);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_levelPath"></param>
	void loadLevel(const std::string& t_levelPath);

private:
	ShapeManager* m_managerPtr;
	std::string m_path;
};

#endif