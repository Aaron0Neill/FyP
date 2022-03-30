#ifndef CREATE_STATE_INCLUDE
#define CREATE_STATE_INCLUDE

#include "IbuildState.h"

enum class ShapeType : uint8_t
{
	NONE		= 255U,
	EDGE		= 2U,
	TRIANGLE	= 3U,
	SQUARE		= 4U,
	PENTAGON	= 5U,
	HEXAGON		= 6U,
	SEPTAGON	= 7U,
	OCTAGON		= 8U,
	CIRCLE		= 9U
};

class CreateState : 
	public IBuildState
{
public:
	/// <summary>
	/// Overloaded constructor used to initialise the renderwindow and the shapemanager
	/// </summary>
	/// <param name="t_window"> Window all the shapes are drawn too </param>
	/// <param name="t_manager"> Manager of all the shapes </param>
	CreateState(sf::RenderWindow* t_window, ShapeManager* t_manager);
	~CreateState()=default;

	/// <summary>
	/// Handle the events while the create state is enabled, 
	/// movement of the shapes and creation of the shapes 
	/// </summary>
	/// <param name="e"> Current event on the window </param>
	void handleEvent(sf::Event& e)override;

	/// <summary>
	/// Draw the preview shape
	/// </summary>
	void render()override;

	/// <summary>
	/// Update the current shape that is being previewd 
	/// </summary>
	/// <param name="t_sides"> number of sides for the new shape </param>
	void updateShape(ShapeType t_sides);
private:

	/// <summary>
	/// Update the drawing of the preview shape
	/// </summary>
	void updateDrawing();

	/// <summary>
	/// Start showing the shape
	/// </summary>
	void showShape();

	Vector m_vertices[b2_maxPolygonVertices];
	Vector m_centrePoint;
	float m_scale{ 1.f };
	sf::VertexArray m_drawing{ sf::LinesStrip };
	sf::CircleShape m_circle;
	uint8 m_currentPoints{ 0U };	
	ShapeType m_currentShape { ShapeType::NONE };
};

#endif