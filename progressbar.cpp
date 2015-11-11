#include "progressbar.h"

#include <QImage>
#include <QPixmap>

ProgressBar::ProgressBar(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    size = QSize(100, 25);
    SetProgress(1);
}

ProgressBar::ProgressBar(QSize size, QGraphicsItem *parent)
{
    this->size = size;
    SetProgress(1);
}

void ProgressBar::SetProgress(qreal percent)
{
    qreal value;
    if(percent>1)
        value=1;
    else if(percent<0)
        value=0;
    else
        value=percent;

    QImage img(size, QImage::Format_RGB888);
    img.fill(qRgb(255,0,0));
    for(int x=0; x<img.width() * value; x++) {
        for(int y=0; y<img.height(); y++)
            img.setPixel(x, y, qRgb(0,255,0));
    }
    QPixmap pxm = QPixmap::fromImage(img);
    this->setPixmap(pxm);
}

