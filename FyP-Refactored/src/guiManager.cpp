#include "guiManager.h"

void GUIManager::init(sf::RenderWindow* t_window)
{
	m_gui = new tgui::Gui(*t_window);
	auto size = t_window->getView().getSize();
	m_gui->setAbsoluteView({ 0,0, size.x ,size.y });
	
	initTextures();
	initShapeBuild();
	initSceneManagment();
	initShapeEditor();
}

//*************************************************************

void GUIManager::handleEvent(sf::Event& e)
{
	m_gui->handleEvent(e);

	if (sf::Event::KeyPressed == e.type)
	{
		if (sf::Keyboard::C == e.key.code)
		{
			m_buildButton->setChecked(true);
		}
	}
}

//*************************************************************

void GUIManager::draw()
{
	m_gui->draw();
}

//*************************************************************

void GUIManager::initShapeBuild()
{
	tgui::Panel::Ptr panel;
	panel = tgui::Panel::create({ 400,1080 });
	panel->setPosition({ 1920 - 400,0 });
	panel->getRenderer()->setBackgroundColor(tgui::Color(109U,26U,54U));
	
	tgui::Group::Ptr group;
	group = tgui::Group::create({ 400,1080 });
	group->setVisible(false);
	
	float picSize = 150.f;
	tgui::Layout2d startPos{ 25.f,125.f };
	tgui::Layout2d rowOffset{ 0.f,200.f };
	tgui::Layout2d colOffset{ 200.f,0.f };

	int index = 0;
	std::vector<tgui::Picture::Ptr> pics;
	
	pics.push_back(tgui::Picture::create(m_shapeTexture[0]));
	pics[index]->setWidgetName("Edge");
	pics[index++]->setPosition(startPos + rowOffset * 3.f + colOffset);

	pics.push_back(tgui::Picture::create(m_shapeTexture[1]));
	pics[index]->setWidgetName("Triangle");
	pics[index++]->setPosition(startPos);

	pics.push_back(tgui::Picture::create(m_shapeTexture[2]));
	pics[index]->setWidgetName("Square");
	pics[index++]->setPosition(startPos + rowOffset);

	pics.push_back(tgui::Picture::create(m_shapeTexture[3]));
	pics[index]->setWidgetName("Pentagon");
	pics[index++]->setPosition(startPos + colOffset);

	pics.push_back(tgui::Picture::create(m_shapeTexture[4]));
	pics[index]->setWidgetName("Hexagon");
	pics[index++]->setPosition(startPos + rowOffset + colOffset);

	pics.push_back(tgui::Picture::create(m_shapeTexture[5]));
	pics[index]->setWidgetName("Septagon");
	pics[index++]->setPosition(startPos + rowOffset * 2.f);

	pics.push_back(tgui::Picture::create(m_shapeTexture[6]));
	pics[index]->setWidgetName("Octagon");
	pics[index++]->setPosition(startPos + rowOffset * 2.f + colOffset);


	auto circleptr = tgui::Picture::create(m_shapeTexture[7]);
	circleptr->setWidgetName("Circle");
	circleptr->setPosition(startPos + rowOffset * 3.f);
	circleptr->onClick([this]() {
		static_cast<CreateState*>(getEditor()->getState().get())->updateShape(ShapeType::CIRCLE);
	});

	group->add(circleptr, circleptr->getWidgetName());

	int i = 2;
	for (auto& ptr : pics)
	{
		ptr->onClick([this, i]() {
			static_cast<CreateState*>(getEditor()->getState().get())->updateShape(static_cast<ShapeType>(i));
			});

		group->add(ptr, ptr->getWidgetName());
		++i;
	}

	panel->add(group, "BuildGroup");

	auto editGroup = tgui::Group::create({ 400,1080 });
	editGroup->setVisible(false);

	auto moveBtn = tgui::Button::create("Move");
	moveBtn->setSize({ 300,100 });
	moveBtn->setPosition({ 50, 100 });
	moveBtn->onClick([this]() { getEditor()->setState(EditState::MOVE); });

	auto rotateBtn = tgui::Button::create("Rotate");
	rotateBtn->setSize({ 300,100 });
	rotateBtn->setPosition({ 50, 225 });
	rotateBtn->onClick([this]() { getEditor()->setState(EditState::ROTATE); });

	auto scaleBtn = tgui::Button::create("Scale");
	scaleBtn->setSize({ 300,100 });
	scaleBtn->setPosition({ 50, 350 });
	scaleBtn->onClick([this]() { getEditor()->setState(EditState::SCALE); });

	auto distJoint = tgui::Button::create("Distance Joint");
	distJoint->setSize({ 300,100 });
	distJoint->setPosition({ 50, 475 });
	distJoint->onClick([this]() { getEditor()->setState(EditState::DISTANCE_JOINT); });

	editGroup->add(moveBtn, "Move");
	editGroup->add(rotateBtn, "Rotate");
	editGroup->add(scaleBtn, "Scale");
	editGroup->add(distJoint, "Distance");

	tgui::RadioButtonGroup::Ptr radioGroup;
	radioGroup = tgui::RadioButtonGroup::create();

	tgui::Label::Ptr createLabel = tgui::Label::create("Create");
	createLabel->setTextSize(24);
	createLabel->setPosition({ 75 - createLabel->getSize().x / 2.f,0});
	createLabel->getRenderer()->setTextColor(tgui::Color::White);

	tgui::Label::Ptr editLabel = tgui::Label::create("Edit");
	editLabel->setTextSize(24);
	editLabel->setPosition({ 200 - editLabel->getSize().x/2.f ,0});
	editLabel->getRenderer()->setTextColor(tgui::Color::White);

	tgui::Label::Ptr shapeLabel = tgui::Label::create("Shape");
	shapeLabel->setTextSize(24);
	shapeLabel->setPosition({ 325 - shapeLabel->getSize().x / 2.f ,0 });
	shapeLabel->getRenderer()->setTextColor(tgui::Color::White);

	m_buildButton = tgui::RadioButton::create();
	m_buildButton->getRenderer()->setTextureUnchecked(m_radioTexture[0]);
	m_buildButton->getRenderer()->setTextureUncheckedHover(m_radioTexture[1]);
	m_buildButton->getRenderer()->setTextureChecked(m_radioTexture[2]);

	m_buildButton->onCheck([group, this]() { 
		group->setVisible(true); 
		getEditor()->setState(EditState::CREATE); 
		});

	m_buildButton->onUncheck([group]() {
		group->setVisible(false);
		});

	m_buildButton->setSize({ 100,50 });
	m_buildButton->setPosition({ 25,25 });

	m_editButton = tgui::RadioButton::create();
	m_editButton->setSize({ 100,50 });
	m_editButton->setPosition({ 150,25 });

	m_editButton->getRenderer()->setTextureUnchecked(m_radioTexture[0]);
	m_editButton->getRenderer()->setTextureUncheckedHover(m_radioTexture[1]);
	m_editButton->getRenderer()->setTextureChecked(m_radioTexture[2]);

	m_editButton->onCheck([this, editGroup]() {
		editGroup->setVisible(true);
		});

	m_editButton->onUncheck([editGroup]() {
		editGroup->setVisible(false);
		});

	radioGroup->add(m_editButton, "Edit");
	radioGroup->add(m_buildButton, "Build");

	panel->add(editGroup, "EditGroup");
	panel->add(radioGroup, "Radio");
	panel->add(createLabel, "createLabel");
	panel->add(editLabel, "editLabel");
	panel->add(shapeLabel, "shapeLabel");

	m_gui->add(panel, "Background");

}

//*************************************************************

void GUIManager::initSceneManagment()
{
	auto panel = m_gui->get<tgui::Panel>("Background");

	auto sceneName = tgui::TextArea::create();
	sceneName->setDefaultText("Input Scene Name");
	sceneName->setSize({ 350,50 });
	sceneName->setPosition({ 25, 900 });
	sceneName->setTextSize(32U);
	sceneName->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	auto saveBtn = tgui::Button::create("Save");
	saveBtn->setPosition({ 25,975 });
	saveBtn->setSize({ 150,75 });
	saveBtn->setTextSize(32U);
	saveBtn->onClick([this, sceneName]()
		{
			if (sceneName->getText().size() != 0)
				this->getLoader()->saveLevel("assets/levels/" + sceneName->getText().toStdString() + ".json");
		});

	auto loadBtn = tgui::Button::create("Load");
	loadBtn->setPosition({ 225,975 });
	loadBtn->setSize({ 150,75 });
	loadBtn->setTextSize(32U);

	panel->add(sceneName, "SceneName");
	panel->add(saveBtn, "SaveButton");
	panel->add(loadBtn, "LoadButton");

	auto fileDialogue = tgui::FileDialog::create("Level Loader", "Load");
	fileDialogue->setPath("assets/levels");
	fileDialogue->setVisible(false);
	fileDialogue->setMultiSelect(false);
	fileDialogue->setFileMustExist(true);
	fileDialogue->setFileTypeFilters({
		{"Level", { "*.json" }}
	});
	fileDialogue->onFileSelect([this, sceneName](const std::vector<tgui::Filesystem::Path>& t_file) {
		if (t_file.size())
		{
			std::string filePath = t_file.at(0).getParentPath().asString().toStdString();
			filePath += "/" + t_file[0].getFilename().toStdString();
			this->getLoader()->loadLevel(filePath);

			auto text = t_file[0].getFilename();
			text = text.substr(0, text.find('.'));

			sceneName->setText(text);
		}
	});

	m_gui->add(fileDialogue, "FolderWindow");

	loadBtn->onClick([fileDialogue]() {
		fileDialogue->setEnabled(true);
		fileDialogue->setVisible(true);
		});
}

//*************************************************************

void GUIManager::initShapeEditor()
{
	/* info to show
		- Position (updating)
		- Rotation (updating)
		- BodyType (changable)
		- Joints (toggleable)
	*/

	auto panel = m_gui->get<tgui::Panel>("Background");
	auto radioGroup = m_gui->get<tgui::RadioButtonGroup>("Radio");
	auto shapeGroup = tgui::Group::create({ 400,1080 });
	shapeGroup->setVisible(false);

	auto shapeButton = tgui::RadioButton::create();
	shapeButton->setSize({ 100,50 });
	shapeButton->setPosition({ 275,25 });

	shapeButton->getRenderer()->setTextureUnchecked(m_radioTexture[0]);
	shapeButton->getRenderer()->setTextureUncheckedHover(m_radioTexture[1]);
	shapeButton->getRenderer()->setTextureChecked(m_radioTexture[2]);

	shapeButton->onClick([this, shapeGroup]() {
		getEditor()->setState(EditState::SELECT);
		shapeGroup->setVisible(true);
		});
	shapeButton->onUncheck([shapeGroup]() {
		shapeGroup->setVisible(false);
		});
	radioGroup->add(shapeButton, "Shape");

	auto idLabel = tgui::Label::create("Current Shape id: ");
	idLabel->setSize({ 400,50 });
	idLabel->setPosition({ 25,85 });
	idLabel->setTextSize(32);
	idLabel->getRenderer()->setTextColor(tgui::Color::White);

	/// <summary>
	/// Position
	/// </summary>
	auto positionLabel = tgui::Label::create("Position");
	positionLabel->setSize({ 150,50 });
	positionLabel->setPosition({ 25,150 });
	positionLabel->setTextSize(32);
	positionLabel->getRenderer()->setTextColor(tgui::Color::White);
	
	auto xValue = tgui::EditBox::create();
	xValue->setPosition({ 175,150 });
	xValue->setSize({ 100,50 });
	xValue->setTextSize(32);
	xValue->setInputValidator("[+-]?[0-9]*\.?[0-9]*");
	
	auto yValue = tgui::EditBox::create();
	yValue->setPosition({ 290, 150 });
	yValue->setSize({ 100,50 });
	yValue->setTextSize(32);
	yValue->setInputValidator("[+-]?[0-9]*\.?[0-9]*");

	/// <summary>
	/// **************************
	/// Rotation
	/// </summary>

	auto rotationLabel = tgui::Label::create("Rotation");
	rotationLabel->setSize({ 150,50 });
	rotationLabel->setPosition({ 25,225 });
	rotationLabel->setTextSize(32);
	rotationLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto rotVal = tgui::EditBox::create();
	rotVal->setSize({ 175, 50 });
	rotVal->setPosition({ 200,225 });
	rotVal->setTextSize(32);
	rotVal->setInputValidator("[+-]?[0-9]*\.?[0-9]*");
	

	/// <summary>
	/// **************************
	/// Type
	/// </summary>

	auto TypeLabel = tgui::Label::create("Body Type");
	TypeLabel->setSize({ 175,50 });
	TypeLabel->setPosition({ 25,300 });
	TypeLabel->setTextSize(32);
	TypeLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto typeBox = tgui::ComboBox::create();
	typeBox->setPosition({ 200,300 });
	typeBox->setSize({ 175, 50 });
	typeBox->addItem("Static Body");
	typeBox->addItem("Kinematic Body");
	typeBox->addItem("Dynamic Body");

	typeBox->onItemSelect([this](int t_index) {
		if (IShape* currentShape = m_builder->getCurrentShape())
		{
			currentShape->setBodyType((b2BodyType)t_index);
		}
	});
	
	
	
	shapeGroup->add(xValue, "ShapeXValue");
	shapeGroup->add(yValue, "ShapeYValue");
	shapeGroup->add(idLabel, "ShapeID");
	shapeGroup->add(positionLabel);
	shapeGroup->add(rotationLabel);
	shapeGroup->add(rotVal, "ShapeRotation");
	shapeGroup->add(TypeLabel);
	shapeGroup->add(typeBox, "ShapeType");
	panel->add(shapeGroup, "modificationGroup");
}

//*************************************************************

void GUIManager::initTextures()
{
	m_shapeTexture = new tgui::Texture[8];
	m_radioTexture = new tgui::Texture[3];

	m_shapeTexture[0] = tgui::Texture("assets/images/Edge.png");
	m_shapeTexture[1] = tgui::Texture("assets/images/Triangle.png");
	m_shapeTexture[2] = tgui::Texture("assets/images/Square.png");
	m_shapeTexture[3] = tgui::Texture("assets/images/Pentagon.png");
	m_shapeTexture[4] = tgui::Texture("assets/images/Hexagon.png");
	m_shapeTexture[5] = tgui::Texture("assets/images/Septagon.png");
	m_shapeTexture[6] = tgui::Texture("assets/images/Octagon.png");
	m_shapeTexture[7] = tgui::Texture("assets/images/Circle.png");

	m_radioTexture[0] = tgui::Texture("assets/images/RadioButtonTex.png");
	m_radioTexture[1] = tgui::Texture("assets/images/RadioButtonHover.png");
	m_radioTexture[2] = tgui::Texture("assets/images/RadioButtonSelected.png");
}
