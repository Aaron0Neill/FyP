#include "levelLoader.h"

void LevelLoader::saveLevel(const std::string& t_levelPath)
{
	std::ofstream file(t_levelPath);

	jsonf data;

	m_managerPtr->saveShapes(data["shapes"]);
	m_managerPtr->saveJoints(data["joints"]);

	if (file.is_open())
	{
		file.clear();
		file << data;
		file.close();
	}
}

//*************************************************************

void LevelLoader::loadLevel(const std::string& t_levelPath)
{
	m_managerPtr->reset();
	std::ifstream file(t_levelPath);

	jsonf data;

	if (file.is_open())
	{
		file >> data;
		file.close();
	}

	ShapeID currID = 0;
	for (auto& shape : data["shapes"])
	{
		b2Shape::Type type = shape["ShapeType"].get<b2Shape::Type>();


		if (shape.contains("Texture"))
		{
			auto name = shape["Texture"].get<std::string>();
			TextureManager* tm = TextureManager::getInstance();
			if (tm->loadTexture(name, m_path + "/" + name))
			{
				currID = m_managerPtr->createSprite(name, { 0,0 });
				(*m_managerPtr)[currID]->fromJson(shape);
				continue;
			}
		}


		if (type == b2Shape::Type::e_polygon)
			currID = m_managerPtr->createPolygon();
		else if (type == b2Shape::Type::e_circle)
			currID = m_managerPtr->createCircle();
		else
		{
			auto pointsPtr = shape["Points"].begin();

			float x1 = (*pointsPtr++);
			float y1 = (*pointsPtr++);
			float x2 = (*pointsPtr++);
			float y2 = (*pointsPtr);

			m_managerPtr->createEdge({ x1,y1 }, { x2,y2 });
			continue;
		}

		(*m_managerPtr)[currID]->fromJson(shape);
	}


	for (auto& jointData : data["joints"])
	{
		auto bodyA = jointData["Bodies"][0].get<ShapeID>();
		auto bodyB = jointData["Bodies"][1].get<ShapeID>();

		m_managerPtr->createDistanceJoint(bodyA, bodyB);
	}
}
