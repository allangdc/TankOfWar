#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QGraphicsPixmapItem>
#include <QSize>
#include <QRgb>

class ProgressBar: public QGraphicsPixmapItem
{
public:
    ProgressBar(QGraphicsItem *parent=NULL);
    ProgressBar(QSize size, QGraphicsItem *parent=NULL);
    void SetProgress(qreal percent);
    void SetProgress();
    void SetColors(QRgb fore, QRgb back);
private:
    QSize size;
    QRgb forecolor, backcolor;
    qreal percent;
};

#endif // PROGRESSBAR_H
