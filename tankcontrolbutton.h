#ifndef TANKCONTROLBUTTON_H
#define TANKCONTROLBUTTON_H

#include <QGraphicsPixmapItem>
#include <QSize>
#include "tank.h"

#define BTN_BLUE ":/image/buttons/image/arrow_blue.png"
#define BTN_SILVER ":/image/buttons/image/arrow_silver.png"

class TankControlButton : public QGraphicsPixmapItem
{
public:
    TankControlButton(Tank *tank);
    virtual void Click(bool is_pressed);
    QSizeF Size();
    QRectF Geometry();
protected:
    Tank *tank;
    QSizeF size;
#ifndef __ANDROID__
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
#else
    virtual bool sceneEvent(QEvent *event);
#endif
};

#endif // TANKCONTROLBUTTON_H
