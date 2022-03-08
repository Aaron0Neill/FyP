#include "levelLoader.h"

void LevelLoader::saveLevel(const std::string& t_levelPath)
{
	std::ofstream file(t_levelPath);

	jsonf data;

	m_managerPtr->saveWorld(data["shapes"]);

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

	auto shapePtr = data["shapes"].begin();
	auto shapeEnd = data["shapes"].end();

	for (; shapePtr != shapeEnd; ++shapePtr)
	{
		jsonf& shapeData = *shapePtr;
		auto type = shapeData["ShapeType"].get<int>();

		if (type == b2Shape::Type::e_circle)
		{
			auto pts = shapeData["Centre"].begin();

			float x = pts->get<float>();
			float y = (++pts)->get<float>();

			float scale = shapeData["Scale"].get<float>();

			auto shape = m_managerPtr->createCircle(scale, {x,y});

			float rot = shapeData["Rotation"].get<float>();
			(*m_managerPtr)[shape]->setRotation(rot);
		}
		else if (type == b2Shape::Type::e_polygon)
		{
			auto xPtr = shapeData["Centre"].begin();
			auto yPtr = shapeData["Centre"].rbegin();

			float x = xPtr->get<float>();
			float y = yPtr->get<float>();
			uint8_t polyCount = shapeData["PolyCount"].get<uint8_t>();

			float scale = shapeData["Scale"].get<float>();

			auto shape = m_managerPtr->createPolygon(polyCount, scale, { x,y });

			float rot = shapeData["Rotation"].get<float>();
			(*m_managerPtr)[shape]->setRotation(rot);
		}
		else if (type == b2Shape::Type::e_edge)
		{
			auto pointsPtr = shapeData["Points"].begin();

			float x1 = pointsPtr->get<float>();
			float y1 = (++pointsPtr)->get<float>();
			float x2 = (++pointsPtr)->get<float>();
			float y2 = (++pointsPtr)->get<float>();

			m_managerPtr->createEdge({ x1,y1 }, { x2,y2 });
		}
	}
}
