#include "tankcontrolbutton.h"
#include <QGraphicsSceneMouseEvent>
#include <QTouchEvent>

TankControlButton::TankControlButton(Tank *tank) : QGraphicsPixmapItem()
{
    size = QSizeF(120,120);
    this->tank = tank;
    this->setTransformOriginPoint(size.width()/2, size.height()/2);
    this->setAcceptTouchEvents(true);
    this->installSceneEventFilter(this);

    QPixmap pxm = QPixmap(BTN_BLUE).scaled(size.toSize(),
                                           Qt::IgnoreAspectRatio,
                                           Qt::SmoothTransformation);
    this->setPixmap(pxm);
}

void TankControlButton::Click(bool is_pressed)
{
    QPixmap pxm;
    if(is_pressed) {
        tank->setSendValue(true);
        pxm = QPixmap(BTN_SILVER).scaled(size.toSize(),
                                               Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);
    } else {
        pxm = QPixmap(BTN_BLUE).scaled(size.toSize(),
                                               Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);
    }
    this->setPixmap(pxm);
}

QSizeF TankControlButton::Size()
{
    return size;
}

QRectF TankControlButton::Geometry()
{
    QRectF rect(this->pos(), Size());
    return rect;
}


#ifndef __ANDROID__
void TankControlButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsPixmapItem::mousePressEvent(e);
    if(e->button() == Qt::LeftButton) {
        Click(true);
    }
}
#endif

#ifndef __ANDROID__
void TankControlButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsPixmapItem::mouseReleaseEvent(e);
    if(e->button() == Qt::LeftButton) {
        Click(false);
    }
}
#endif

#ifdef __ANDROID__
bool TankControlButton::sceneEvent(QEvent *event) {
    switch (event->type()) {
        case QEvent::TouchBegin:
            Click(true);
        break;
        case QEvent::TouchUpdate:
        break;
        case QEvent::TouchEnd:
            Click(false);
        break;
    }
    return true;
}

/*
bool TankControlButton::sceneEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
            QList<QTouchEvent::TouchPoint> pts = static_cast<QTouchEvent *>(event)->touchPoints();
            int released = 0;
            for(QList<QTouchEvent::TouchPoint>::iterator it=pts.begin(); it != pts.end(); it++)
            {
                switch(it->state()) {
                    case Qt::TouchPointReleased:
                        released++;
                        break;
                    case Qt::TouchPointMoved:
                    {
                        QRectF rect = it->rect();
                        if(rect.isEmpty()) {
                            qreal diameter = qreal(50) * it->pressure();
                            rect.setSize(QSizeF(diameter, diameter));
                        }
                        if(!it->rect().isEmpty() && !it->rect().intersects(this->Geometry())) {
                            released++;
                        } else {
                            released = 0;
                            Click(true);
                        }
                    }
                        break;
                    default:
                        released = 0;
                        Click(true);
                        break;
                }
            }
            if(released == pts.size())
                Click(false);
            break;
        }
        default:
            return QGraphicsPixmapItem::sceneEvent(event);
    }
    return true;
}
*/
#endif
