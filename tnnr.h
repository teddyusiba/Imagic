#ifndef TNNR_H
#define TNNR_H

#include "algorithm.h"

class TNNR: public Algorithm
{
public:
    TNNR(int i, QImage image, QLabel *label);
    ~TNNR();

    QImage work();

private:
    int index;
    QImage ori_img;
    QLabel* label_result;
};

#endif // TNNR_H
