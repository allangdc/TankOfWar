#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QGraphicsPixmapItem>
#include <QSize>

class ProgressBar: public QGraphicsPixmapItem
{
public:
    ProgressBar(QGraphicsItem *parent=NULL);
    ProgressBar(QSize size, QGraphicsItem *parent=NULL);
    void SetProgress(qreal percent);
private:
    QSize size;
};

#endif // PROGRESSBAR_H
