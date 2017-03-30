
#ifndef GLOBAL_H
#define GLOBAL_H

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#pragma  warning (disable : 4819)

class Global
{	
public:
	static Global * getInstance();
	~Global();

	static dimension2d<u32>   screenDimension();
	static stringw            screenDimensionString();

	inline void               setStart(bool b)   { IsStart=b;}
	inline bool               isStart()          { return IsStart==true;}

	inline stringw            dataPath()        { return DataPath;};
	inline stringw            uiPath()          { return UIPath;}
	
	inline E_DRIVER_TYPE      driverType()      { return DriverType;}
private:
	Global();

	E_DRIVER_TYPE             DriverType;

	bool                      IsStart;
	stringw                   DataPath;
	stringw                   UIPath;
};
#endif