#include "tank.h"

#include <QtMath>
#include <QObject>
#include <QGraphicsScene>
#include <QDebug>

Tank::Tank() : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/image/tank/image/yellow.png").scaled(QSize(80,80),
                                                              Qt::IgnoreAspectRatio,
                                                              Qt::SmoothTransformation));  //imagem do tanque;
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setRotation(0);
    action = STOP;
    setInterval(100);
}

void Tank::RotateLeft(bool run)
{
    if(run)
        action |= GO_LEFT;
    else
        action &= ~GO_LEFT;
    this->start();
}

void Tank::RotateRight(bool run)
{
    if(run)
        action |= GO_RIGHT;
    else
        action &= ~GO_RIGHT;
    this->start();
}

void Tank::MoveFoward(bool run)
{
    if(run)
        action |= GO_FORWARD;
    else
        action &= ~GO_FORWARD;
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

int Tank::Action()
{
    return action;
}

void Tank::timerEvent(QTimerEvent *e)
{
    if(action & GO_LEFT == GO_LEFT) {
        PulseLeft();
    }
    if(action & GO_FORWARD == GO_FORWARD) {
        PulseForward();
    }
    if(action & GO_RIGHT == GO_RIGHT) {
        PulseRight();
    }
    if(action == STOP) {
        this->stop();
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
