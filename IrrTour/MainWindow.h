#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include "Global.h"

class MainWindow: public  IEventReceiver 
{
	enum GUI_ID
	{
		GUI_ID_ONJONG_BUTTON = 0,
		GUI_ID_EXIT_BUTTON   = 1,

	};

	enum REGION_ID
	{
		REGION_ID_ONJONG =0
	};

public:
	MainWindow();
	~MainWindow();
	
	virtual bool OnEvent(const irr::SEvent &event);

	void run();
	
private:
	void draw();
	bool init();
	void setupGUI();

	bool onGUIEvent(const SEvent &event);
	bool onKeyEvent(const SEvent &event);
private:
	E_DRIVER_TYPE     DriverType;
	bool              IsFullScreen;

	SColor            BackgroundColor;
	dimension2d<u32>  Dimension;

	IrrlichtDevice    *Device;
	IVideoDriver      *Driver;
	IGUIEnvironment   *GUIEnv;

	REGION_ID         RegionID;
	
	static int        ButtonGapWidth;
	static int        ButtonGapHeight;
};

#endif