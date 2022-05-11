#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 生成注册表信息用于储存最近文件
    QCoreApplication::setOrganizationName(QString("Digia"));
    QCoreApplication::setApplicationName(QString("Qt"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
