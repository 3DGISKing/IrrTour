#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>

#include "Global.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


Global::Global()
{
	DriverType=EDT_OPENGL;
	IsStart = false;

	QString qstrpath = QCoreApplication::applicationDirPath();

	stringw wstrpath(qstrpath.toAscii().data(), qstrpath.toAscii().size() );

	DataPath = wstrpath + L"/onjong";
	UIPath = wstrpath + L"/ui";
}

Global::~Global()
{

}



Global * Global::getInstance()
{
	static Global instance; 
	return &instance; 
}


dimension2d<u32> Global::screenDimension()
{
	QRect rect=QApplication::desktop()->screenGeometry();
	
	dimension2d<u32> d(rect.width(),rect.height()); 

	return d;
}

stringw Global::screenDimensionString()
{
	QRect rect=QApplication::desktop()->screenGeometry();

	QString str=QString("%1_%2").arg(rect.width()).arg(rect.height());

	return stringw(str.toAscii().data());
}