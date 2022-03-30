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
	std::ifstream file(t_levelPath);

	jsonf data;

	if (file.is_open())
	{
		file >> data;
		file.close();
	}

	for (auto& shape : data["shapes"])
	{
		b2Shape::Type type = shape["ShapeType"].get<b2Shape::Type>();

		ShapeID currID = 0;

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
