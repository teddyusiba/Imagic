#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QImage>
#include <QLabel>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = nullptr);

    virtual QImage work() = 0;

signals:

public slots:
};

#endif // ALGORITHM_H
