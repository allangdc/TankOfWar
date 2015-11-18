#include "bomb.h"
#include "tank.h"
#include <QTimerEvent>
#include <QtMath>
#include <QGraphicsScene>
#include <QList>


Bomb::Bomb(QGraphicsScene *scene): QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(BOMB_IMAGE).scaled(QSize(20,20),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setInterval(1000.0f/FRAME_BOMB);
    this->scene = scene;
    steps=0;
}

Bomb::Bomb(QGraphicsScene *scene, QPointF position, qreal angle): QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(BOMB_IMAGE).scaled(QSize(30,30),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setInterval(50);
    setPos(position);
    SetAngle(angle);
    this->scene = scene;
    steps=0;
}

void Bomb::Fire()
{
    scene->addItem(this);
    this->start();
}

void Bomb::SetAngle(qreal angle)
{
    setRotation(angle);
}

void Bomb::SetID(int value)
{
    id = value;
}

int Bomb::ID()
{
    return id;
}

void Bomb::timerEvent(QTimerEvent *e)
{
    PulseForward();
}

void Bomb::PulseForward()
{
    steps++;
    if(steps >= MAX_STEPS)
        this->deleteLater();

    QPointF pt = this->pos();
    qreal radian = qDegreesToRadians(rotation());
    pt.setX(pt.x() + STEP_BOMB * qSin(radian));
    pt.setY(pt.y() - STEP_BOMB * qCos(radian));
    setPos(pt);

    QList<QGraphicsItem *> colliding = this->collidingItems();
    for(QList<QGraphicsItem *>::iterator it = colliding.begin();
        it != colliding.end();
        it++)
    {
        Tank *tank = dynamic_cast<Tank *>(*it);
        if(tank) {
            tank->HitByBomb(this);
        }
    }
}















