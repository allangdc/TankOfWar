#include "progressbar.h"

#include <QImage>
#include <QPixmap>

ProgressBar::ProgressBar(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    forecolor = qRgb(0,255,0);  // green
    backcolor = qRgb(255,0,0);  // red
    size = QSize(100, 25);
    SetProgress(1);
}

ProgressBar::ProgressBar(QSize size, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    forecolor = qRgb(0,255,0);  // green
    backcolor = qRgb(255,0,0);  // red
    this->size = size;
    SetProgress(1);
}

void ProgressBar::SetProgress(qreal percent)
{
    this->percent = percent;
    qreal value;
    if(percent>1)
        value=1;
    else if(percent<0)
        value=0;
    else
        value=percent;

    QImage img(size, QImage::Format_RGB888);
    img.fill(backcolor);
    for(int x=0; x<img.width() * value; x++) {
        for(int y=0; y<img.height(); y++)
            img.setPixel(x, y, forecolor);
    }
    QPixmap pxm = QPixmap::fromImage(img);
    this->setPixmap(pxm);
}

void ProgressBar::SetProgress()
{
    SetProgress(percent);
}

void ProgressBar::SetColors(QRgb fore, QRgb back)
{
    forecolor = fore;
    backcolor = back;
    SetProgress();
}

