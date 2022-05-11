#ifndef GREY_H
#define GREY_H

#include "algorithm.h"

class GREY : public Algorithm
{
public:
    GREY(int i, QImage image, QLabel *label);
    ~GREY();

    QImage greyScale();
    QImage redChannel();
    QImage greenChannel();
    QImage blueChannel();
    void showImage(QImage res);
    QImage work();

private:
    int index;
    QImage ori_image;
    QLabel *label_result;
};

#endif // GREY_H
