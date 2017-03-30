#include <assert.h>

#include "MainWindow.h"

int MainWindow::ButtonGapWidth=50;
int MainWindow::ButtonGapHeight=100;

MainWindow::MainWindow()
{
	DriverType      = EDT_OPENGL;
	IsFullScreen    = true;

	BackgroundColor.set(255,100,101,140);

	Dimension=Global::screenDimension();
}

MainWindow::~MainWindow()
{
	
}

bool MainWindow::init()
{
	Device=	createDevice( video::EDT_SOFTWARE, Dimension, 32, IsFullScreen, false, false, this);
	
	if(!Device)
		return false;
	
	Driver=Device->getVideoDriver();
	GUIEnv=Device->getGUIEnvironment();

	setupGUI();

	return true;
}

void MainWindow::setupGUI()
{
	stringw uipath=Global::getInstance()->uiPath();

	stringw dimensionstring=Global::screenDimensionString();

	//add background image
	GUIEnv->addImage(Driver->getTexture(uipath+"background_"+dimensionstring+".bmp"),position2d<s32>(0,0));
	
	//add buttons

	ITexture *normalimage=Driver->getTexture(uipath+"/onjong_normal.png");
	ITexture *pressedimage=Driver->getTexture(uipath+"/onjong_pressed.png");

	dimension2d<u32> imagesize=normalimage->getOriginalSize();

	rect<int> buttonrect(ButtonGapWidth,                 ButtonGapHeight
		                ,ButtonGapWidth+imagesize.Width, ButtonGapHeight+imagesize.Height);

	IGUIButton* button= GUIEnv->addButton(buttonrect);

	button->setID(GUI_ID_ONJONG_BUTTON);
	button->setImage(normalimage);
	button->setPressedImage(pressedimage);
	button->setDrawBorder(false);
	button->setUseAlphaChannel(true);

    buttonrect.UpperLeftCorner.set(ButtonGapWidth,ButtonGapHeight+imagesize.Height+ButtonGapHeight);
	buttonrect.LowerRightCorner.set(ButtonGapWidth+imagesize.Width,ButtonGapHeight+imagesize.Height+ButtonGapHeight+imagesize.Height);

	button= GUIEnv->addButton(buttonrect);

	normalimage=Driver->getTexture(uipath+"/exit_normal.png");
	pressedimage=Driver->getTexture(uipath+"/exit_pressed.png");

	button->setID(GUI_ID_EXIT_BUTTON);
	button->setImage(normalimage);
	//button->setPressedImage(pressedimage);
	button->setDrawBorder(false);
	button->setUseAlphaChannel(true);
}


void MainWindow::draw()
{
	Driver->beginScene(true, true, BackgroundColor);
	GUIEnv->drawAll();
	Driver->endScene();
}

bool MainWindow::OnEvent(const SEvent &event)
{
	if (event.EventType == EET_GUI_EVENT)
		return onGUIEvent(event);
	else if(event.EventType == EET_KEY_INPUT_EVENT)
		return onKeyEvent(event);

	return false;
}


bool MainWindow::onKeyEvent(const SEvent &event)
{
	EKEY_CODE keycode=event.KeyInput.Key;

	if (keycode==KEY_ESCAPE && event.KeyInput.PressedDown==false)
	{
		Global::getInstance()->setStart(false);
		Device->closeDevice();
		return true;
	}

	return false;
}


bool MainWindow::onGUIEvent(const SEvent &event)
{
	s32 id = event.GUIEvent.Caller->getID();

	if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED && id==GUI_ID_ONJONG_BUTTON)
	{
		RegionID=REGION_ID_ONJONG;
		Global::getInstance()->setStart(true);

		Device->closeDevice();
		return true;
	}

	if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED && id==GUI_ID_EXIT_BUTTON)
	{
		//GUIEnv->addMessageBox( L"Quit",L"Do you want to quit?",true,EMBF_YES|EMBF_NO);
		
		Global::getInstance()->setStart(false);
		Device->closeDevice();
	
		return true;
	}

	return false;
}

void MainWindow::run()
{
	if(!init())
	{
		return;
	}

	while(Device->run())
	{
		if(Device->isWindowActive())
			draw();
		else
			Device->yield();
	}

	Device->drop();
}

