#include "HikVisionCJPrj.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HikVisionCJPrj w;
	w.show();
	return a.exec();
}
