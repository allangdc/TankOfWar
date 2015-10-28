#include "tank.h"

#include <QtMath>
#include <QObject>

Tank::Tank() : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/image/tank/image/yellow.png"));                            //imagem do tanque;
    setScale(0.5);
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setRotation(0);
    action = STOP;
    setInterval(100);
}

void Tank::RotateLeft()
{
    action = GO_LEFT;
    this->start();
}

void Tank::RotateRight()
{
    action = GO_RIGHT;
    this->start();
}

void Tank::MoveFoward()
{
    action = GO_FORWARD;
    this->start();
}

void Tank::MoveStop()
{
    action = STOP;
}

void Tank::SetOrientation(QPoint position, double angle)
{
    SetOrientation(position.x(), position.y(), angle);
}

void Tank::SetOrientation(int x, int y, double angle)
{
    QPointF pt(x, y);
    setPos(pt);
    setRotation(angle);
}

void Tank::timerEvent(QTimerEvent *e)
{
    switch (action) {
    case STOP:
        this->stop();
        break;
    case GO_FORWARD:
        PulseForward();
        break;
    case GO_LEFT:
        PulseLeft();
        break;
    case GO_RIGHT:
        PulseRight();
        break;
    default:
        break;
    }
}

void Tank::PulseLeft()
{
    setRotation(rotation() - STEP);
}

void Tank::PulseRight()
{
    setRotation(rotation() + STEP);
}

void Tank::PulseForward()
{
    QPointF pt = this->pos();
    double radian = qDegreesToRadians(rotation());
    pt.setX(pt.x() + STEP * qSin(radian));
    pt.setY(pt.y() - STEP * qCos(radian));
    setPos(pt);
}
