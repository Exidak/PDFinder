// PDFinder.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PDFinder.h"
#include "MainWnd.h"

int main(int argc, char* argv[])
{
	QApplication App(argc, argv);
	App.setWindowIcon(QIcon(":/favicon"));
	MainWnd wnd;
	wnd.show();
	return App.exec();
}
