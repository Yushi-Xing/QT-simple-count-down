#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//解决高分辨率显示不全
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(400,300);
    w.show();

    return a.exec();
}
