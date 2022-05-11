#include "grey.h"
#include "qthread.h"

GREY::GREY(int i, QImage image, QLabel *label): index(i), ori_image(image)
{
    label_result = label;  // 不知道有没有更好的处理办法
}

GREY::~GREY()
{
    label_result = nullptr;
}

QImage GREY::greyScale()
{
    QImage newImage = QImage(ori_image.width(), ori_image.height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x < newImage.width(); x++)
    {
        for(int y = 0; y < newImage.height(); y++)
        {
            oldColor = QColor(ori_image.pixel(x,y));
            int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
            newImage.setPixel(x, y, qRgb(average, average, average));
        }
    }
    return newImage;
}

QImage GREY::redChannel()
{
    QImage newImage = QImage(ori_image.width(), ori_image.height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x < newImage.width(); x++)
    {
        for(int y = 0; y < newImage.height(); y++)
        {
            oldColor = QColor(ori_image.pixel(x,y));
            newImage.setPixel(x, y, qRgb(oldColor.red(), oldColor.red(), oldColor.red()));
        }
    }
    return newImage;
}

QImage GREY::greenChannel()
{
    QImage newImage = QImage(ori_image.width(), ori_image.height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x < newImage.width(); x++)
    {
        for(int y = 0; y < newImage.height(); y++)
        {
            oldColor = QColor(ori_image.pixel(x,y));
            newImage.setPixel(x, y, qRgb(oldColor.green(), oldColor.green(), oldColor.green()));
        }
    }
    return newImage;
}


QImage GREY::blueChannel()
{
    QImage newImage = QImage(ori_image.width(), ori_image.height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x < newImage.width(); x++)
    {
        for(int y = 0; y < newImage.height(); y++)
        {
            oldColor = QColor(ori_image.pixel(x,y));
            newImage.setPixel(x, y, qRgb(oldColor.blue(), oldColor.blue(), oldColor.blue()));
        }
    }
    return newImage;
}

void GREY::showImage(QImage res)
{
    QImage output = res.scaled(label_result->width(), label_result->height(), Qt::KeepAspectRatio);
    label_result->setPixmap(QPixmap::fromImage(output));
}

QImage GREY::work()
{
    QImage res;
    switch (index) {
    case 1:
        res = greyScale();
        showImage(res);
        break;
    case 2:
        res = redChannel();
        showImage(res);
        break;
    case 3:
        res = greenChannel();
        showImage(res);
        break;
    case 4:
        res = blueChannel();
        showImage(res);
        break;
    default:
        break;
    }
    return res;
}

