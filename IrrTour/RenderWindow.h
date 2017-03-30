#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "Global.h"

class SceneController;

class RenderWindow: public IEventReceiver
{
public:
	RenderWindow();
	~RenderWindow();

	virtual bool         OnEvent(const irr::SEvent &event);

	void                 run();

	IrrlichtDevice*      device()       {return Device;}
	IVideoDriver*        driver()       {return Driver;}
	ISceneManager*       sceneManager() {return SceneMgr;}

private:
	bool                 init();
	void                 setupStartupScreen();
	
	void                 draw();
	bool                 onGUIEvent(const SEvent &event);
	bool                 onKeyEvent(const SEvent &event);
private:
	IrrlichtDevice*      Device;
	IVideoDriver*        Driver;
	ISceneManager*       SceneMgr; 

	SceneController*     _SceneController;

	IGUIStaticText*      StatusText;
	IGUIInOutFader*      InOutFader;
	SColor               BackColor;

};
#endif