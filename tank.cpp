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
    setInterval(100);
    direction=0;
    forward = false;
}

void Tank::RotateLeft(bool run)
{
    if(run)
        direction = -1;
    else if(direction<0) {
        direction = 0;
    }
    this->start();
}

void Tank::RotateRight(bool run)
{
    if(run)
        direction = 1;
    else if(direction>0) {
        direction = 0;
    }
    this->start();
}

void Tank::MoveFoward(bool run)
{
    forward = run;
    this->start();
}

void Tank::MoveStop()
{
    forward = false;
    direction = 0;
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
    if(direction<0) {
        PulseLeft();
    }
    if(forward==true) {
        PulseForward();
    }
    if(direction>0) {
        PulseRight();
    }
    if(direction==0 && forward==false) {
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
