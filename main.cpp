#include "mainwindow.h"
#include "./qu3e/q3.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
