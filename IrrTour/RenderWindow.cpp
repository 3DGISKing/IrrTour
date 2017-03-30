#include "RenderWindow.h"

#include "SceneController.h"

RenderWindow::RenderWindow()
{

}

RenderWindow::~RenderWindow()
{
	
}

bool RenderWindow::init()
{
	dimension2d<u32> dimension=Global::screenDimension();

	E_DRIVER_TYPE drivertype=Global::getInstance()->driverType();

	Device=	createDevice(drivertype, dimension, 32, true, false, false, this);

	if(!Device)
		return false;

	Driver   = Device->getVideoDriver();
	SceneMgr = Device->getSceneManager();

	return true;
}

void RenderWindow::run()
{
	if(!init())
		return;

	setupStartupScreen();
	draw();

	_SceneController=new SceneController(this);
	
	InOutFader->fadeIn(30000);

	s32 lastfps = 0;
	wchar_t tmp[255];

	while (Device->run())
	{
		if(Device->isWindowActive())
			draw();
		else
			Device->yield();

		// write statistics
		const s32 nowfps = Driver->getFPS();

		swprintf(tmp, 255, L"%ls fps:%3d triangles:%0.3f mio/s",
			Driver->getName(), Driver->getFPS(),
			Driver->getPrimitiveCountDrawn(1) * (1.f / 1000000.f));

		StatusText->setText(tmp);
		if ( nowfps != lastfps )
			
			lastfps = nowfps;
	}

	Device->drop();	
}

bool RenderWindow::onKeyEvent(const SEvent &event)
{
	EKEY_CODE keycode=event.KeyInput.Key;

	if (keycode==KEY_ESCAPE && event.KeyInput.PressedDown==false)
	{
		Device->closeDevice();
		return true;
	}

	return false;
}


bool RenderWindow::onGUIEvent(const SEvent &event)
{
	s32 id = event.GUIEvent.Caller->getID();

	return false;
}

bool RenderWindow::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == EET_GUI_EVENT)
		return onGUIEvent(event);
	else if(event.EventType == EET_KEY_INPUT_EVENT)
		return onKeyEvent(event);

	return false;
}

void RenderWindow::draw()
{
	Driver->beginScene(true, true, BackColor );

	SceneMgr->drawAll();
	Device->getGUIEnvironment()->drawAll();

	Driver->endScene();
}

void RenderWindow::setupStartupScreen()
{
	core::dimension2d<u32> size = Device->getVideoDriver()->getScreenSize();

	Device->getCursorControl()->setVisible(false);

	// setup loading screen

	BackColor.set(255,90,90,156);

	// create in fader

	InOutFader = Device->getGUIEnvironment()->addInOutFader();
	InOutFader->setColor(BackColor,	video::SColor ( 0, 230, 230, 230 ));

	// loading text

	const int lwidth = size.Width - 20;
	const int lheight = 16;

	core::rect<int> pos(10, size.Height-lheight-10, 10+lwidth, size.Height-10);

	Device->getGUIEnvironment()->addImage(pos);
	StatusText = Device->getGUIEnvironment()->addStaticText(L"Loading...",	pos, true);
	StatusText->setOverrideColor(video::SColor(255,205,200,200));

	// load bigger font

	Device->getGUIEnvironment()->getSkin()->setFont(
		Device->getGUIEnvironment()->getFont("./font/fonthaettenschweiler.bmp"));

	// set new font color

	Device->getGUIEnvironment()->getSkin()->setColor(gui::EGDC_BUTTON_TEXT,
		video::SColor(255,100,100,100));
}