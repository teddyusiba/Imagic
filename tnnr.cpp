#include "tnnr.h"

TNNR::TNNR(int i, QImage image, QLabel *label): index(i), ori_img(image)
{
    label_result = label;  // 不知道有没有更好的处理办法
}


TNNR::~TNNR()
{
    label_result = nullptr;
}

QImage TNNR::work()
{
    return ori_img;
}
