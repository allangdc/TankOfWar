#include "tank.h"
#include "bomb.h"

#include <QtMath>
#include <QObject>
#include <QGraphicsScene>
#include <QDebug>

Tank::Tank(QGraphicsScene *scene) : QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(TANK_IMAGE).scaled(QSize(80,80),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));  //imagem do tanque;
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setRotation(0);
    setInterval(100);
    direction=0;
    forward = false;
    this->scene = scene;
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

void Tank::Fire()
{
    Bomb *bomb = new Bomb(scene);
    QPointF pt;     //position of the bomb
    QPointF ori;    //center of the rotation
    pt.setY(this->y() - bomb->pixmap().height()/2);
    pt.setX(this->x() + this->pixmap().width()/2 - bomb->pixmap().width()/2);
    ori.setX(bomb->pixmap().width()/2);
    ori.setY(this->transformOriginPoint().y() + bomb->pixmap().height()/2);

    bomb->setPos(pt);
    bomb->setTransformOriginPoint(ori);
    bomb->SetAngle(this->rotation());
    bomb->Fire();
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
