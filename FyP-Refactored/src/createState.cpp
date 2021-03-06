#include "createState.h"
#include "guiManager.h"

IShape* IBuildState::m_selectedShape { nullptr };
b2Joint* IBuildState::m_selectedJoint { nullptr };

CreateState::CreateState(sf::RenderWindow* t_window) :
	IBuildState(t_window),
	m_centrePoint({}), m_currentShape(ShapeType::NONE)
{
	m_drawing.resize(b2_maxPolygonVertices + 1);
	for (int i = 0; i < b2_maxPolygonVertices; ++i)
		m_drawing[i].color = sf::Color({ 40U,40U,40U,255U });

	m_circle.setFillColor(sf::Color::Transparent);
	m_circle.setOutlineThickness(-1.5f);
	m_circle.setOutlineColor({ 40U,40U,40U,255U });
	m_circle.setRadius(PixelsPerMetre);
	m_circle.setOrigin({ PixelsPerMetre, PixelsPerMetre });

	m_currentSprite.setColor(sf::Color(255U, 255U, 255U, 100U));
}

//*************************************************************

void CreateState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		m_centrePoint = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
		updateDrawing();
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code >= sf::Keyboard::Num3 && e.key.code <= sf::Keyboard::Num9)
			updateShape(static_cast<ShapeType>(e.key.code - sf::Keyboard::Num0));
		else if (e.key.code == sf::Keyboard::Escape)
			m_currentShape = ShapeType::NONE;
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
			if (m_centrePoint.x < 1920.f)
				if (m_currentShape >= ShapeType::TRIANGLE && m_currentShape <= ShapeType::OCTAGON)
					m_manager->createPolygon(m_currentPoints, 1, m_centrePoint);
				else if (m_currentShape == ShapeType::CIRCLE)
					m_manager->createCircle(1, m_centrePoint);
				else if (m_currentShape == ShapeType::EDGE)
					if (m_drawing[1].position.x == -10)
					{
						m_drawing[0].position = m_centrePoint;
						m_drawing[1].position = m_centrePoint;
					}
					else
					{
						m_manager->createEdge(m_drawing[0].position, m_centrePoint);
						for (int i = 0; i < 2; ++i)
							m_drawing[i].position = { -10.f,-10.f };
					}
				else if (m_currentShape == ShapeType::SPRITE)
					if (m_textureLoaded)
						m_manager->createSprite(m_currentName, m_centrePoint);
	}
	else if (sf::Event::MouseWheelScrolled == e.type)
	{

	}
}

//*************************************************************

void CreateState::render()
{
	if (m_currentShape >= ShapeType::EDGE && m_currentShape < ShapeType::CIRCLE)
		m_window->draw(&m_drawing[0], m_currentPoints + 1, sf::LinesStrip);
	else if (m_currentShape == ShapeType::CIRCLE)
		m_window->draw(m_circle);
	else if (m_currentShape == ShapeType::SPRITE)
		m_window->draw(m_currentSprite);
}

//*************************************************************

void CreateState::updateShape(ShapeType t_type)
{
	m_currentShape = t_type;
	switch (t_type)
	{
	case ShapeType::NONE:
		break;
	case ShapeType::EDGE:
		m_currentPoints = 1U;
		for (int i = 0; i < 2; ++i)
			m_drawing[i].position = { -10,-10 };
		break;
	case ShapeType::TRIANGLE:
	case ShapeType::SQUARE:
	case ShapeType::PENTAGON:
	case ShapeType::HEXAGON:
	case ShapeType::SEPTAGON:
	case ShapeType::OCTAGON:
		m_currentPoints = (uint8_t)t_type;
		showShape();
		break;
	case ShapeType::SPRITE:
		loadSprite();
		break;
	default:
		break;
	}
	updateDrawing();
}

//*************************************************************

void CreateState::updateDrawing()
{
	if (m_currentShape >= ShapeType::TRIANGLE && m_currentShape <= ShapeType::OCTAGON)
	{
		float cosAngle = cosf(0.f);
		float sinAngle = sinf(0.f);

		if (m_currentShape == ShapeType::SQUARE)
		{
			cosAngle = cosf(45.f * Deg2Rad);
			sinAngle = sinf(45.f * Deg2Rad);
		}

		Vector vertexPos;

		for (uint8 i = 0; i < m_currentPoints + 1; ++i)
		{
			Vector vertice = m_vertices[i % m_currentPoints];
			Vector rotation = { (cosAngle * vertice.x) - (sinAngle * vertice.y),
								(cosAngle * vertice.y) + (sinAngle * vertice.x) };
			vertexPos = rotation + m_centrePoint.toWorldSpace();
			m_drawing[i].position = vertexPos.fromWorldSpace();

			m_drawing[i].color = sf::Color::Black;
		}
	}
	else if (m_currentShape == ShapeType::CIRCLE)
		m_circle.setPosition(m_centrePoint);
	else if (m_currentShape == ShapeType::EDGE)
	{
		if (m_drawing[0].position.x != -10.f)
			m_drawing[1].position = m_centrePoint;
	}
	else if (m_currentShape == ShapeType::SPRITE)
	{
		if (m_textureLoaded)
		{
			Vector size = m_currentSprite.getTexture()->getSize();
			m_currentSprite.setPosition(m_centrePoint - size / 2.f);
		}
	}
}

//*************************************************************

void CreateState::showShape()
{
	auto points = PolygonShape::getPoints(m_currentPoints, 1);

	for (int i = 0; i < m_currentPoints; ++i)
		m_vertices[i] = Vector(points[i]);

	delete points;
}

//*************************************************************

void CreateState::loadSprite()
{
	m_textureLoaded = false;
	tgui::Gui* gui = GUIManager::getInstance()->getGui();

	auto fileLoader = tgui::FileDialog::create("Load Texture");
	fileLoader->setPath("assets/Textures");
	fileLoader->setMultiSelect(false);
	fileLoader->setFileMustExist(true);
	fileLoader->setFileTypeFilters({
		{"Texture", { "*.png" }}
		});
	fileLoader->onFileSelect([this](const std::vector<tgui::Filesystem::Path>& t_file) {
		if (t_file.size())
		{
			std::string fileName = t_file[0].getFilename().toStdString();
			std::string filePath = t_file.at(0).getParentPath().asString().toStdString();
			filePath += "/" + t_file[0].getFilename().toStdString();

			TextureManager* tm = TextureManager::getInstance();

			if (tm->loadTexture(fileName, filePath))
			{
				Texture tx = tm->getTexture(fileName);
				m_currentName = fileName;
				m_currentSprite.setTexture(*tx);
				m_currentSprite.setTextureRect({ 0,0,(int)tx->getSize().x, (int)tx->getSize().y });
				m_textureLoaded = true;
			}
		}
		});
	gui->add(fileLoader);
}
