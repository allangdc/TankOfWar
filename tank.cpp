#include "tank.h"
#include "bomb.h"
#include "progressbar.h"

#include <QtMath>
#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include <QSound>

Tank::Tank(QGraphicsScene *scene) : QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(TANK_IMAGE).scaled(QSize(80,80),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));  //imagem do tanque;
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setInterval(1000.0f / qreal(FRAME_TANK));
    direction=0;
    forward = false;
    this->scene = scene;
    progress = new ProgressBar(QSize(this->pixmap().width(), this->pixmap().width()/8), this);
    progress->setTransformOriginPoint(progress->pixmap().width()/2,
                                      -(this->pixmap().height() + 10 + progress->pixmap().height()/2)/2);
    progress->setPos(this->x(), this->y());
    scene->addItem(progress);
    setRotation(0);
    life = 100;

    sound_fire = new QSound(FIRE_SOUND);
    sound_drive = new QSound(DRIVE_TANK_SOUND);
}

Tank::~Tank()
{
    delete progress;
}

void Tank::RotateLeft(bool run)
{
    if(run) {
        if(direction!=-1)
            PulseLeft();
        direction = -1;
    }
    else if(direction<0) {
        direction = 0;
    }
    this->start();
}

void Tank::RotateRight(bool run)
{
    if(run) {
        if(direction!=1)
            PulseRight();
        direction = 1;
    }
    else if(direction>0) {
        direction = 0;
    }
    this->start();
}

void Tank::MoveFoward(bool run)
{
    if(forward != run)
        PulseForward();
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
    sound_fire->play();
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

    life-=10;
    progress->SetProgress((qreal) life/ 100.0);
}

void Tank::setPos(qreal x, qreal y)
{
    setPos(QPoint(x, y));
}

void Tank::setPos(QPointF point)
{
    QGraphicsPixmapItem::setPos(point);
    progress->setPos(point.x(), point.y() + pixmap().height() + 10);
}

void Tank::setRotation(qreal angle)
{
    QGraphicsPixmapItem::setRotation(angle);
    progress->setRotation(angle);
}

void Tank::timerEvent(QTimerEvent *e)
{
    if(direction==0 && forward==false) {
        this->stop();
    } else {
        if(direction<0) {
            PulseLeft();
        }
        if(forward==true) {
            PulseForward();
        }
        if(direction>0) {
            PulseRight();
        }
    }
}

void Tank::PulseLeft()
{
    setRotation(rotation() - STEP_TANK);
}

void Tank::PulseRight()
{
    setRotation(rotation() + STEP_TANK);
}

void Tank::PulseForward()
{
    QPointF pt = this->pos();
    double radian = qDegreesToRadians(rotation());
    pt.setX(pt.x() + STEP_TANK * qSin(radian));
    pt.setY(pt.y() - STEP_TANK * qCos(radian));
    setPos(pt);
}
