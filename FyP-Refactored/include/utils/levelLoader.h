#ifndef LEVEL_LOADER_INCLUDE
#define LEVEL_LOADER_INCLUDE

#include "shapeManager.h"
#include "json.hpp"
#include <fstream>

class LevelLoader
{
public:
	LevelLoader(ShapeManager* t_manager) :
		m_managerPtr(t_manager) {};
	~LevelLoader()=default;

	void saveLevel(const std::string& t_levelPath);

	void loadLevel(const std::string& t_levelPath);

private:
	ShapeManager* m_managerPtr;
};

#endif