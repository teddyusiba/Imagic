#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::greyPara(int i, QImage image, QLabel *label)
{
    algorithm = new GREY(i, image, label);
}

void MyThread::tnnrPara(int i, QImage image, QLabel *label)
{
    algorithm = new TNNR(i, image, label);
}

void MyThread::run()
{

    QImage res = algorithm->work();

    emit outPut(res);
}
