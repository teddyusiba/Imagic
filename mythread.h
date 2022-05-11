#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QImage>
#include <QLabel>
#include "algorithm.h"
#include "grey.h"
#include "tnnr.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    void greyPara(int i, QImage image, QLabel *label);
    void tnnrPara(int i, QImage image, QLabel *label);

protected:
    virtual void run() override;

private:
    Algorithm *algorithm;

signals:
    void outPut(QImage res);

public slots:
};

#endif // MYTHREAD_H
