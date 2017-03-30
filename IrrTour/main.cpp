#include <QtGui/QApplication>

#include "Mainwindow.h"
#include "RenderWindow.h"
#include "Global.h"

int main(int argc,char** argv)
{
	QApplication a(argc,argv);

start:

	MainWindow mainwnd;

	mainwnd.run();
	
	if(Global::getInstance()->isStart())
	{
		RenderWindow renderwnd;

		renderwnd.run();
		
		goto start;

	}
	else
		return 0;
}