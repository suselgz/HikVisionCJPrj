#include "QHikVisionTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QHikVisionTest w;
	w.show();
	return a.exec();
}
