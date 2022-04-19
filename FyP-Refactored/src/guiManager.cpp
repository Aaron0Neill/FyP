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
	initJoint();
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

void GUIManager::updateSelectedShape(IShape* t_selectedShape)
{
	auto group = m_gui->get<tgui::Group>("modificationGroup");

	std::string name = t_selectedShape->getName();
	auto nameBox = group->get<tgui::EditBox>("ShapeName");
	nameBox->setText(name);

	Vector shapePos = t_selectedShape->getBody()->GetPosition();
	shapePos = shapePos.fromWorldSpace();
	auto xPos = group->get<tgui::EditBox>("ShapeXValue");
	auto yPos = group->get<tgui::EditBox>("ShapeYValue");
	xPos->setText(std::to_string(shapePos.x));
	yPos->setText(std::to_string(shapePos.y));

	xPos->setCaretPosition(0);
	yPos->setCaretPosition(0);

	float angle = t_selectedShape->getBody()->GetAngle() * Rad2Deg;
	auto rot = group->get<tgui::EditBox>("ShapeRotation");
	rot->setText(std::to_string(angle));

	rot->setCaretPosition(0);

	auto type = t_selectedShape->getBody()->GetType();
	auto typeBox = group->get<tgui::ComboBox>("ShapeType");
	typeBox->setSelectedItemByIndex(type);

	sf::Vector2f scale = t_selectedShape->getScale();
	auto xScale = group->get<tgui::EditBox>("ShapeXScale");
	auto yScale = group->get<tgui::EditBox>("ShapeYScale");
	auto xyscale = group->get<tgui::EditBox>("ShapeScale");

	if (t_selectedShape->getFixture()->GetType() == b2Shape::Type::e_circle)
	{
		xyscale->setVisible(true);
		xyscale->setText(std::to_string(scale.x));
	}
	else
	{
		xyscale->setVisible(false);
		xScale->setText(std::to_string(scale.x));
		yScale->setText(std::to_string(scale.y));
	}

	xScale->setCaretPosition(0);
	yScale->setCaretPosition(0);

	bool isTrigger = t_selectedShape->getFixture()->IsSensor();
	auto TriggerBox = group->get<tgui::CheckBox>("ShapeTrigger");
	TriggerBox->setChecked(isTrigger);

	float density = t_selectedShape->getFixture()->GetDensity();
	auto densityBox = group->get<tgui::EditBox>("ShapeDensity");
	densityBox->setText(std::to_string(density));

	float restitution = t_selectedShape->getFixture()->GetRestitution();
	auto restitutionBox = group->get<tgui::Slider>("ShapeRestitution");
	restitutionBox->setValue(restitution);

	float friction = t_selectedShape->getFixture()->GetFriction();
	auto frictionBox = group->get<tgui::Slider>("ShapeFriction");
	frictionBox->setValue(friction);
}

//*************************************************************

void GUIManager::updateSelectedJoint(b2Joint* t_selectedJoint)
{
	b2JointType type = t_selectedJoint->GetType();
	
	if (type == b2JointType::e_distanceJoint)
	{
		b2DistanceJoint* distJnt = static_cast<b2DistanceJoint*>(t_selectedJoint);
		// update Info 
		tgui::Group::Ptr grp = m_gui->get<tgui::Group>("DistJoint");

		tgui::EditBox::Ptr currLen = grp->get<tgui::EditBox>("CurrentLength");
		currLen->setText(std::to_string(distJnt->GetLength()));

		tgui::EditBox::Ptr minLen = grp->get<tgui::EditBox>("MinLength");
		minLen->setText(std::to_string(distJnt->GetMinLength()));

		tgui::EditBox::Ptr maxLen = grp->get<tgui::EditBox>("MaxLength");
		maxLen->setText(std::to_string(distJnt->GetMaxLength()));
	}
	else if (type == b2JointType::e_wheelJoint)
	{

	}
	else
		std::cout << "Unknown joint\n";

}

//*************************************************************

void GUIManager::initShapeBuild()
{
	tgui::Panel::Ptr panel;
	panel = tgui::Panel::create({ 400,1080 });
	panel->setPosition({ 1920,0 });
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

	auto wheelJoint = tgui::Button::create("Wheel Joint");
	wheelJoint->setSize({ 300,100 });
	wheelJoint->setPosition({ 50, 600 });
	wheelJoint->onClick([this]() { getEditor()->setState(EditState::WHEEL_JOINT); });

	editGroup->add(moveBtn, "Move");
	editGroup->add(rotateBtn, "Rotate");
	editGroup->add(scaleBtn, "Scale");
	editGroup->add(distJoint, "Distance");
	editGroup->add(wheelJoint, "Wheel");

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
	float indent = 25.f;
	float yLevel = 85.f;
	float spacing = 45.f;

	tgui::Layout2d buttonSize{ 175,40 };

	auto radioGroup = m_gui->get<tgui::RadioButtonGroup>("Radio");
	auto panel = m_gui->get<tgui::Panel>("Background");
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

	auto nameLabel = tgui::Label::create("Shape Name");
	nameLabel->setSize({ 185,40 });
	nameLabel->setPosition({ indent, yLevel });
	nameLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	nameLabel->setTextSize(20U);
	nameLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto nameBox = tgui::EditBox::create();
	nameBox->setSize({ 175,40 });
	nameBox->setPosition({ 200, yLevel });
	nameBox->setTextSize(20U);
	nameBox->setInputValidator("^[a-zA-Z]+$");
	nameBox->onTextChange([this](tgui::String t_newText) {
		if (IShape* current = m_builder->getCurrentShape())
			current->setName(t_newText.toStdString());
		});

	yLevel += spacing;

	auto idLabel = tgui::Label::create("Current Shape id: ");
	idLabel->setSize({ 400,40 });
	idLabel->setPosition({ indent, yLevel });
	idLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	idLabel->setTextSize(20U);
	idLabel->getRenderer()->setTextColor(tgui::Color::White);

	yLevel += spacing;

	/// <summary>
	/// Position
	/// </summary>
	auto positionLabel = tgui::Label::create("Position");
	positionLabel->setSize(buttonSize);
	positionLabel->setPosition({ indent,yLevel });
	positionLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	positionLabel->setTextSize(20U);
	positionLabel->getRenderer()->setTextColor(tgui::Color::White);
	
	auto xValue = tgui::EditBox::create();
	xValue->setPosition({ 200, yLevel });
	xValue->setSize({ buttonSize.x / 2.f, buttonSize.y });
	xValue->setTextSize(20U);
	xValue->setInputValidator(tgui::EditBox::Validator::Float);
	xValue->onTextChange([this](tgui::String t_newText) {
		if (!t_newText.size())
			return;

		if (t_newText.size() == 1 && t_newText[0] == '-')
			return;

		float newX = stof(t_newText.toStdString());
		getEditor()->getCurrentShape()->setXPosition(newX);
		});
	
	auto yValue = tgui::EditBox::create();
	yValue->setPosition({ 287.5f, yLevel });
	yValue->setSize({ buttonSize.x / 2.f, buttonSize.y });
	yValue->setTextSize(20U);
	yValue->setInputValidator(tgui::EditBox::Validator::Float);
	yValue->onTextChange([this](tgui::String t_newText) {
		if (!t_newText.size())
			return;

		if (t_newText.size() == 1 && t_newText[0] == '-')
			return;

		float newY = stof(t_newText.toStdString());
		getEditor()->getCurrentShape()->setYPosition(newY);
		});

	yLevel += spacing;

	/// <summary>
	/// **************************
	/// Rotation
	/// </summary>
	auto rotationLabel = tgui::Label::create("Rotation");
	rotationLabel->setSize(buttonSize);
	rotationLabel->setPosition({ 25,yLevel });
	rotationLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	rotationLabel->setTextSize(20U);
	rotationLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto rotVal = tgui::EditBox::create();
	rotVal->setSize(buttonSize);
	rotVal->setPosition({ 200,yLevel });
	rotVal->setTextSize(20U);
	rotVal->setInputValidator(tgui::EditBox::Validator::Float);
	rotVal->onTextChange([this](tgui::String t_newText) {
		if (!t_newText.size())
			return;

		if (t_newText.size() == 1 && t_newText[0] == '-')
			return;

		getEditor()->getCurrentShape()->setRotation(stof(t_newText.toStdString()));
		});
	
	yLevel += spacing;

	/// <summary>
	/// **************************
	/// Type
	/// </summary>
	auto typeLabel = tgui::Label::create("Body Type");
	typeLabel->setSize({ 175,40 });
	typeLabel->setPosition({ 25,yLevel });
	typeLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	typeLabel->setTextSize(20U);
	typeLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto typeBox = tgui::ComboBox::create();
	typeBox->setPosition({ 200,yLevel });
	typeBox->setSize({ 175, 40 });
	typeBox->setTextSize(16U);
	typeBox->addItem("Static Body");
	typeBox->addItem("Kinematic Body");
	typeBox->addItem("Dynamic Body");

	typeBox->onItemSelect([this](int t_index) {
		if (IShape* currentShape = m_builder->getCurrentShape())
		{
			currentShape->setBodyType((b2BodyType)t_index);
		}
	});

	yLevel += spacing;
	
	/// <summary>
	/// **************************
	/// Scale
	/// </summary>
	auto scaleLabel = tgui::Label::create("Scale");
	scaleLabel->setSize({ 150,40 });
	scaleLabel->setPosition({ indent, yLevel });
	scaleLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	scaleLabel->setTextSize(20U);
	scaleLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto xScale = tgui::EditBox::create();
	xScale->setPosition({ 200, yLevel });
	xScale->setSize({ buttonSize.x / 2.f, buttonSize.y });
	xScale->setTextSize(20U);
	xScale->setInputValidator(tgui::EditBox::Validator::Float);

	xScale->onTextChange([this](const tgui::String& t_newText) {
		float newScale;

		if (!t_newText.attemptToFloat(newScale)) return;

		if (IShape* shape = m_builder->getCurrentShape())
			shape->setXScale(newScale);
		});

	auto yScale = tgui::EditBox::create();
	yScale->setPosition({ 287.5f, yLevel });
	yScale->setSize({ buttonSize.x / 2.f, buttonSize.y });
	yScale->setTextSize(20U);
	yScale->setInputValidator(tgui::EditBox::Validator::Float);
	yScale->onTextChange([this](const tgui::String& t_newText) {
		float newScale;

		if (!t_newText.attemptToFloat(newScale)) return;

		if (IShape* shape = m_builder->getCurrentShape())
			shape->setYScale(newScale);
		});

	auto xyScale = tgui::EditBox::create();
	xyScale->setPosition({ 200.f, yLevel });
	xyScale->setVisible(false);
	xyScale->setSize({ buttonSize.x, buttonSize.y });
	xyScale->setTextSize(20U);
	xyScale->setInputValidator(tgui::EditBox::Validator::Float);
	xyScale->onTextChange([this](const tgui::String& t_newText) {
		float newScale;

		if (!t_newText.attemptToFloat(newScale)) return;

		if (IShape* shape = m_builder->getCurrentShape())
			shape->setScale(newScale);
		});

	yLevel += spacing;

	/// <summary>
	/// **************************
	/// Trigger
	/// </summary>
	auto triggerLabel = tgui::Label::create("Trigger");
	triggerLabel->setSize({ 235,40 });
	triggerLabel->setPosition({ 25,yLevel });
	triggerLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	triggerLabel->setTextSize(20U);
	triggerLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto triggerCheckbox = tgui::CheckBox::create();
	triggerCheckbox->setPosition({ 265, yLevel });
	triggerCheckbox->setSize({50,40});
	triggerCheckbox->onChange([this](bool t_newState) {
		if (IShape* shape = m_builder->getCurrentShape())
			shape->getFixture()->SetSensor(t_newState);
		});

	yLevel += spacing;

	/// <summary> 
	/// **************************
	/// Density
	/// </summary>
	auto densityLabel = tgui::Label::create("Density");
	densityLabel->setSize({ 235,40 });
	densityLabel->setPosition({ 25,yLevel });
	densityLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	densityLabel->setTextSize(20U);
	densityLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto densityEditBox = tgui::EditBox::create();
	densityEditBox->setPosition({ 200, yLevel });
	densityEditBox->setSize(buttonSize);
	densityEditBox->setTextSize(20U);
	densityEditBox->setInputValidator(tgui::EditBox::Validator::Float);
	densityEditBox->onTextChange([this](tgui::String t_newText) {
		if (!t_newText.size())
			return;

		auto density = std::stof(t_newText.toStdString());
		if (IShape* shape = m_builder->getCurrentShape())
			shape->getFixture()->SetDensity(density);
		});

	yLevel += spacing;
	
	/// <summary> 
	/// **************************
	/// Restitution Slider
	/// </summary>
	auto RestitutionLabel = tgui::Label::create("Restitution");
	RestitutionLabel->setSize({ 200,40 });
	RestitutionLabel->setPosition({ 25,yLevel });
	RestitutionLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	RestitutionLabel->setTextSize(20U);
	RestitutionLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto RestitutionSlider = tgui::Slider::create(0.f, 1.f);
	RestitutionSlider->setStep(0.05f);
	RestitutionSlider->setSize({ 175,20 });
	RestitutionSlider->setPosition({ 200,yLevel + 10 });
	RestitutionSlider->onValueChange([this](float t_newRestitution) 
		{
			if (IShape* shape = m_builder->getCurrentShape())
				shape->getFixture()->SetRestitution(t_newRestitution);
		});

	yLevel += spacing;

	/// <summary> 
	/// **************************
	/// Friction Slider
	/// </summary>
	auto FrictionLabel = tgui::Label::create("Friction");
	FrictionLabel->setSize({ 200,40 });
	FrictionLabel->setPosition({ 25,yLevel });
	FrictionLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	FrictionLabel->setTextSize(20U);
	FrictionLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto FrictionSlider = tgui::Slider::create(0.f, 1.f);
	FrictionSlider->setStep(0.05f);
	FrictionSlider->setSize({ 175,20 });
	FrictionSlider->setPosition({ 200,yLevel + 10 });
	FrictionSlider->onValueChange([this](float t_newFriction)
		{
			if (IShape* shape = m_builder->getCurrentShape())
			{ 
				shape->getFixture()->SetFriction(t_newFriction);
				std::cout << "Setting friction to: " << t_newFriction << std::endl;
			}
		});



	/// <summary>
	/// **************************
	/// add the shapes
	/// </summary>
	shapeGroup->add(nameLabel);
	shapeGroup->add(nameBox, "ShapeName");
	shapeGroup->add(idLabel, "ShapeID");
	shapeGroup->add(xValue, "ShapeXValue");
	shapeGroup->add(yValue, "ShapeYValue");
	shapeGroup->add(positionLabel);
	shapeGroup->add(rotationLabel);
	shapeGroup->add(rotVal, "ShapeRotation");
	shapeGroup->add(typeLabel);
	shapeGroup->add(typeBox, "ShapeType");
	shapeGroup->add(scaleLabel);
	shapeGroup->add(xScale, "ShapeXScale");
	shapeGroup->add(yScale, "ShapeYScale");
	shapeGroup->add(xyScale, "ShapeScale");
	shapeGroup->add(triggerCheckbox, "ShapeTrigger");
	shapeGroup->add(triggerLabel);
	shapeGroup->add(densityLabel);
	shapeGroup->add(densityEditBox, "ShapeDensity");
	shapeGroup->add(RestitutionLabel);
	shapeGroup->add(RestitutionSlider, "ShapeRestitution");
	shapeGroup->add(FrictionLabel);
	shapeGroup->add(FrictionSlider, "ShapeFriction");
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

//*************************************************************

void GUIManager::initJoint()
{
	auto panel = m_gui->get<tgui::Panel>("Background");
	auto distanceGroup = tgui::Group::create({ 400,1080 });
	auto wheelGroup = tgui::Group::create({ 400,1080 });
	distanceGroup->setVisible(false);
	wheelGroup->setVisible(false);

	float indent = 25.f;
	float yLevel = 85.f;
	float spacing = 45.f;
	unsigned labelFontSize = 20U;
	tgui::Layout2d buttonSize{ 175,40 };

	//dj 
	//dj.collideConnected; //bool
	//dj.damping; //float
	//dj.length; // float (curr len)
	//dj.minLength; // float
	//dj.maxLength; // float
	//dj.localAnchorA; // b2Vec
	//dj.localAnchorB; // b2vec
	//dj.stiffness; //float

	/// <summary>
	/// Can Collide
	/// </summary>
	auto canCollideLabel = tgui::Label::create("Can Collide");
	canCollideLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	canCollideLabel->setTextSize(labelFontSize);
	canCollideLabel->setSize({ 175,40 });
	canCollideLabel->setPosition({ indent, yLevel });
	canCollideLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto canCollide = tgui::CheckBox::create();
	canCollide->setPosition({ 265,yLevel });
	canCollide->setSize({ 50,40 });
	canCollide->onChange([this](bool t_currState) {

		});

	yLevel += spacing;

	/// <summary>
	/// Damping
	/// </summary>
	auto dampingLabel = tgui::Label::create("Damping");
	dampingLabel->setPosition({indent, yLevel});
	dampingLabel->setTextSize(labelFontSize);
	dampingLabel->setSize({ 175,40 });
	dampingLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	dampingLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto damping = tgui::EditBox::create();
	damping->setInputValidator(tgui::EditBox::Validator::Float);
	damping->setPosition({ 200,yLevel });
	damping->setSize(buttonSize);

	yLevel += spacing;
	/// <summary>
	/// Current Length
	/// </summary>
	auto currLenLabel = tgui::Label::create("Current Length");
	currLenLabel->setPosition({ indent, yLevel });
	currLenLabel->setTextSize(labelFontSize);
	currLenLabel->setSize({ 175,40 });
	currLenLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	currLenLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto currLen = tgui::EditBox::create();
	currLen->setInputValidator(tgui::EditBox::Validator::Float);
	currLen->setPosition({ 200,yLevel });
	currLen->setSize(buttonSize);
	currLen->onTextChange([this](const tgui::String& t_newString) {
		float newLen;
		if (!t_newString.attemptToFloat(newLen)) return;

		if (auto joint = m_builder->getEditor()->getCurrentJoint())
			static_cast<b2DistanceJoint*>(joint)->SetLength(newLen);
		});

	yLevel += spacing;
	/// <summary>
	/// Min Length
	/// </summary>
	auto minLenLabel = tgui::Label::create("Min Length");
	minLenLabel->setPosition({ indent, yLevel });
	minLenLabel->setTextSize(labelFontSize);
	minLenLabel->setSize({ 175,40 });
	minLenLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	minLenLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto minLen = tgui::EditBox::create();
	minLen->setInputValidator(tgui::EditBox::Validator::Float);
	minLen->setPosition({ 200,yLevel });
	minLen->setSize(buttonSize);
	minLen->onTextChange([this](const tgui::String& t_newString) {
		float newLen;
		if (!t_newString.attemptToFloat(newLen)) return;

		if (auto joint = m_builder->getEditor()->getCurrentJoint())
			static_cast<b2DistanceJoint*>(joint)->SetMinLength(newLen);
		});


	yLevel += spacing;
	/// <summary>
	/// Max Length
	/// </summary>
	auto maxLenLabel = tgui::Label::create("Max Length");
	maxLenLabel->setPosition({ indent, yLevel });
	maxLenLabel->setTextSize(labelFontSize);
	maxLenLabel->setSize({ 175,40 });
	maxLenLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	maxLenLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto maxLen = tgui::EditBox::create();
	maxLen->setInputValidator(tgui::EditBox::Validator::Float);
	maxLen->setPosition({ 200,yLevel });
	maxLen->setSize({ 50,40 });

	yLevel += spacing;
	/// <summary>
	/// Local Anchor A
	/// </summary>
	auto localAnchorALabel = tgui::Label::create("Anchor A");
	localAnchorALabel->setPosition({ indent, yLevel });
	localAnchorALabel->setTextSize(labelFontSize);
	localAnchorALabel->setSize({ 175,40 });
	localAnchorALabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	localAnchorALabel->getRenderer()->setTextColor(tgui::Color::White);


	yLevel += spacing;
	/// <summary>
	/// Local Anchor B
	/// </summary>
	auto localAnchorBLabel = tgui::Label::create("Anchor B");
	localAnchorBLabel->setPosition({ indent, yLevel });
	localAnchorBLabel->setTextSize(labelFontSize);
	localAnchorBLabel->setSize({ 175,40 });
	localAnchorBLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	localAnchorBLabel->getRenderer()->setTextColor(tgui::Color::White);


	yLevel += spacing;
	/// <summary>
	/// Stiffness 
	/// </summary>
	auto stiffnessLabel = tgui::Label::create("Stiffness");
	stiffnessLabel->setPosition({ indent, yLevel });
	stiffnessLabel->setTextSize(labelFontSize);
	stiffnessLabel->setSize({ 175,40 });
	stiffnessLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	stiffnessLabel->getRenderer()->setTextColor(tgui::Color::White);

	auto stiffness = tgui::EditBox::create();
	stiffness->setInputValidator(tgui::EditBox::Validator::Float);
	stiffness->setPosition({ 200,yLevel });
	stiffness->setSize(buttonSize);


	/// <summary>
	/// Adding 
	/// </summary>
	distanceGroup->add(canCollideLabel);
	distanceGroup->add(dampingLabel);
	distanceGroup->add(currLenLabel);
	distanceGroup->add(maxLenLabel);
	distanceGroup->add(minLenLabel);
	distanceGroup->add(localAnchorALabel);
	distanceGroup->add(localAnchorBLabel);
	distanceGroup->add(stiffnessLabel);
	distanceGroup->add(canCollide, "canCollide");
	distanceGroup->add(damping, "Damping");
	distanceGroup->add(currLen, "CurrentLength");
	distanceGroup->add(minLen, "MinLength");
	distanceGroup->add(maxLen, "MaxLength");
	//distanceGroup->add(damping, "Damping");
	//distanceGroup->add(damping, "Damping");
	distanceGroup->add(stiffness, "Stiffness");


	//wj
	//wj.collideConnected; //bool
	//wj.damping; //float
	//wj.enableLimit; //bool
	//wj.enableMotor; //bool
	//wj.localAnchorA; // b2vec2
	//wj.localAnchorB; // b2vec2
	//wj.lowerTranslation; //float 
	//wj.maxMotorTorque; //float
	//wj.motorSpeed; //float
	//wj.stiffness; //float
	//wj.upperTranslation; //float 


	panel->add(distanceGroup, "DistJoint");
	panel->add(wheelGroup, "WheelJoint");
}
