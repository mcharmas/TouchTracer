#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCoreApplication::setOrganizationName("TC");
    QCoreApplication::setOrganizationDomain("TouchTracer.com");
    QCoreApplication::setApplicationName("TouchTracer");
    w.show();

    return a.exec();
}
