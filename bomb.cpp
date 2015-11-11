#include "bomb.h"
#include <QTimerEvent>
#include <QtMath>
#include <QGraphicsScene>

Bomb::Bomb(QGraphicsScene *scene): QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(BOMB_IMAGE).scaled(QSize(20,20),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setInterval(1000.0f/FRAME_BOMB);
    this->scene = scene;
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

void Bomb::timerEvent(QTimerEvent *e)
{
    PulseForward();
}

void Bomb::PulseForward()
{
    QPointF pt = this->pos();
    qreal radian = qDegreesToRadians(rotation());
    pt.setX(pt.x() + STEP_BOMB * qSin(radian));
    pt.setY(pt.y() - STEP_BOMB * qCos(radian));
    setPos(pt);
}

