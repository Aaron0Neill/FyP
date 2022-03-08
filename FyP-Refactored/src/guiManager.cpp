#include "guiManager.h"

void GUIManager::init(sf::RenderWindow* t_window)
{
	m_gui = new tgui::Gui(*t_window);
	auto size = t_window->getView().getSize();
	m_gui->setAbsoluteView({ 0,0, size.x ,size.y });
	
	initShapeBuild();
	initSceneManagment();
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
	panel = tgui::Panel::create();
	panel->setSize({ 400,1080 });
	panel->setPosition({ 1920 - 400,0 });
	panel->setWidgetName("ShapeBackground");
	panel->getRenderer()->setBackgroundColor(tgui::Color(109U,26U,54U));
	
	tgui::Group::Ptr group;
	group = tgui::Group::create({ 400,1080 });
	group->setVisible(false);

	tgui::Texture triangleTex("assets/images/Triangle.png");
	tgui::Texture squareTex("assets/images/Square.png");
	tgui::Texture pentagoTex("assets/images/Pentagon.png");
	tgui::Texture hexagonTex("assets/images/Hexagon.png");
	tgui::Texture septagonTex("assets/images/Septagon.png");
	tgui::Texture octagonTex("assets/images/Octagon.png");
	tgui::Texture circleTex("assets/images/Circle.png");
	tgui::Texture edgeTex("assets/images/Edge.png");
	tgui::Texture radioTex("assets/images/RadioButtonTex.png");
	tgui::Texture radioHover("assets/images/RadioButtonHover.png");
	tgui::Texture radioSelected("assets/images/RadioButtonSelected.png");
	
	float picSize = 150.f;
	tgui::Layout2d startPos{ 25.f,125.f };
	tgui::Layout2d rowOffset{ 0.f,200.f };
	tgui::Layout2d colOffset{ 200.f,0.f };

	int index = 0;
	std::vector<tgui::Picture::Ptr> pics;

	pics.push_back(tgui::Picture::create(triangleTex));
	pics[index]->setWidgetName("Triangle");
	pics[index++]->setPosition(startPos);

	pics.push_back(tgui::Picture::create(squareTex));
	pics[index]->setWidgetName("Square");
	pics[index++]->setPosition(startPos + rowOffset);

	pics.push_back(tgui::Picture::create(pentagoTex));
	pics[index]->setWidgetName("Pentagon");
	pics[index++]->setPosition(startPos + colOffset);

	pics.push_back(tgui::Picture::create(hexagonTex));
	pics[index]->setWidgetName("Hexagon");
	pics[index++]->setPosition(startPos + rowOffset + colOffset);

	pics.push_back(tgui::Picture::create(septagonTex));
	pics[index]->setWidgetName("Septagon");
	pics[index++]->setPosition(startPos + rowOffset * 2.f);

	pics.push_back(tgui::Picture::create(octagonTex));
	pics[index]->setWidgetName("Octagon");
	pics[index++]->setPosition(startPos + rowOffset * 2.f + colOffset);

	pics.push_back(tgui::Picture::create(edgeTex));
	pics[index]->setWidgetName("Edge");
	pics[index++]->setPosition(startPos + rowOffset * 3.f + colOffset);

	auto circleptr = tgui::Picture::create(circleTex);
	circleptr->setWidgetName("Circle");
	circleptr->setPosition(startPos + rowOffset * 3.f);
	circleptr->onClick([this]() {
		static_cast<CreateState*>(this->getBuilder()->getState().get())->updatePoints(9);
	});

	group->add(circleptr, circleptr->getWidgetName());

	int i = 3;
	for (auto& ptr : pics)
	{
		ptr->onClick([this, i]() {
			static_cast<CreateState*>(this->getBuilder()->getState().get())->updatePoints(i);
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
	moveBtn->onClick([this]() { this->getBuilder()->setState(EditState::MOVE); });

	auto rotateBtn = tgui::Button::create("Rotate");
	rotateBtn->setSize({ 300,100 });
	rotateBtn->setPosition({ 50, 225 });
	rotateBtn->onClick([this]() { this->getBuilder()->setState(EditState::ROTATE); });

	auto scaleBtn = tgui::Button::create("Scale");
	scaleBtn->setSize({ 300,100 });
	scaleBtn->setPosition({ 50, 350 });
	scaleBtn->onClick([this]() { this->getBuilder()->setState(EditState::SCALE); });

	editGroup->add(moveBtn, "Move");
	editGroup->add(rotateBtn, "Rotate");
	editGroup->add(scaleBtn, "Scale");

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
	m_buildButton->getRenderer()->setTextureChecked(radioSelected);
	m_buildButton->getRenderer()->setTextureUnchecked(radioTex);
	m_buildButton->getRenderer()->setTextureUncheckedHover(radioHover);

	m_buildButton->onCheck([group, this]() { 
		group->setVisible(true); 
		this->getBuilder()->setState(EditState::CREATE); 
		});

	m_buildButton->onUncheck([group]() {
		group->setVisible(false);
		});

	m_buildButton->setSize({ 100,50 });
	m_buildButton->setPosition({ 25,25 });

	m_editButton = tgui::RadioButton::create();
	m_editButton->setSize({ 100,50 });
	m_editButton->setPosition({ 150,25 });

	m_editButton->getRenderer()->setTextureChecked(radioSelected);
	m_editButton->getRenderer()->setTextureUnchecked(radioTex);
	m_editButton->getRenderer()->setTextureUncheckedHover(radioHover);

	m_editButton->onCheck([this, editGroup]() {
		editGroup->setVisible(true);
		});

	m_editButton->onUncheck([editGroup]() {
		editGroup->setVisible(false);
		});

	auto shapeButton = tgui::RadioButton::create();
	shapeButton->setSize({ 100,50 });
	shapeButton->setPosition({ 275,25 });

	shapeButton->getRenderer()->setTextureChecked(radioSelected);
	shapeButton->getRenderer()->setTextureUnchecked(radioTex);
	shapeButton->getRenderer()->setTextureUncheckedHover(radioHover);

	radioGroup->add(m_editButton, "Edit");
	radioGroup->add(m_buildButton, "Build");
	radioGroup->add(shapeButton, "Shape");

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
