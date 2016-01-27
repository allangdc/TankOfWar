#include "tank.h"
#include "bomb.h"
#include "progressbar.h"
#include "sound.h"
#include "scenegame.h"
#include "protocol.h"

#include <QtMath>
#include <QTime>
#include <QObject>
#include <QDebug>
#include <QTimerEvent>

Tank::Tank(SceneGame *scene) : QGraphicsPixmapItem(), QTimer()
{
    setPixmap(QPixmap(TANK_IMAGE).scaled(QSize(80,80),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));  //imagem do tanque;
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
    setInterval(1000.0f / qreal(FRAME_TANK));
    direction=0;
    forward = false;
    action = 0;
    send_value = false;
    this->scene = scene;
    // adjusting progress bars
    progress = new ProgressBar(QSize(this->pixmap().width(), this->pixmap().width()/8), this);
    progress->setTransformOriginPoint(progress->pixmap().width()/2,
                                      -(this->pixmap().height() + 10 + progress->pixmap().height()/2)/2);
    progress->setPos(this->x(), this->y());

    progress_reload_weapon = new ProgressBar(QSize(this->pixmap().width(), this->pixmap().width()/8), this);
    progress_reload_weapon->setTransformOriginPoint(progress_reload_weapon->pixmap().width()/2,
                                                    -(this->pixmap().height() + 10 + progress_reload_weapon->pixmap().height()/2)/2);
    progress_reload_weapon->setPos(this->x(), this->y() + this->pixmap().height()*1.3);
    progress_reload_weapon->SetColors(qRgb(0,0,255), qRgb(255,0,255));


    scene->addItem(progress);
    setRotation(0);
    life = 100;

    sound_fire = new Sound(FIRE_SOUND);
    sound_drive = new Sound(DRIVE_TANK_SOUND);
    sound_explosion = new Sound(EXPLOSION_SOUND);

    QTime now = QTime::currentTime();
    while(now == QTime::currentTime());
    qsrand(now.msec());
    id = qrand();

    reload_weapon = 0;
    progress_reload_weapon->SetProgress(0);
    time_load_weapon = new QTimer();
    time_load_weapon->setInterval(50);
    connect(time_load_weapon, SIGNAL(timeout()), this, SLOT(IncrementWeapon()));
    time_load_weapon->start();
}

Tank::Tank(SceneGame *scene, QPointF position, qreal angle)
    :Tank(scene)
{
    setPos(position);
    setRotation(angle);
}

Tank::~Tank()
{
    delete sound_fire;
    delete sound_drive;
    delete sound_explosion;
    delete progress;
    delete progress_reload_weapon;
    delete time_load_weapon;
}

void Tank::RotateLeft(bool run)
{
    Protocol p(scene);
    if(run) {
        if(direction!=-1) {

            action |= Protocol::MOVE_LEFT;
            if(!scene->IsServer()) {
                p.SendTankPosition(this, action);
            } else {
                p.GenerateMap();
            }

            PulseLeft();
        }
        direction = -1;
    }
    else if(direction<0) {

        action &= ~Protocol::MOVE_LEFT;
        if(!scene->IsServer()) {
            p.SendTankPosition(this, action);
        } else {
            p.GenerateMap();
        }

        direction = 0;
    }
    this->start();
}

void Tank::RotateRight(bool run)
{
    Protocol p(scene);
    if(run) {
        if(direction!=1) {

            action |= Protocol::MOVE_RIGHT;
            if(!scene->IsServer()) {
                p.SendTankPosition(this, action);
            } else {
                p.GenerateMap();
            }

            PulseRight();
        }
        direction = 1;
    }
    else if(direction>0) {

        Protocol p(scene);
        action &= ~Protocol::MOVE_RIGHT;
        if(!scene->IsServer()) {
            p.SendTankPosition(this, action);
        } else {
            p.GenerateMap();
        }

        direction = 0;
    }
    this->start();
}

void Tank::MoveFoward(bool run)
{
    if(forward != run) {

        Protocol p(scene);
        if(run)
            action |= Protocol::MOVE_UP;
        else
            action &= ~Protocol::MOVE_UP;
        if(!scene->IsServer()) {
            p.SendTankPosition(this, action);
        } else {
            p.GenerateMap();
        }


        PulseForward();
    }
    forward = run;
    this->start();
}

void Tank::MoveStop()
{
    Protocol p(scene);
    action &= ~(Protocol::MOVE_UP | Protocol::MOVE_LEFT | Protocol::MOVE_RIGHT);
    if(!scene->IsServer()) {
        p.SendTankPosition(this, action);
    } else {
        p.GenerateMap();
    }
    forward = false;
    direction = 0;
}

void Tank::SetOrientation(QPoint position, double angle)
{
    SetOrientation(position.x(), position.y(), angle);
}

void Tank::SetOrientation(qreal x, qreal y, qreal angle)
{
    QPointF pt(x, y);
    setPos(pt);
    setRotation(angle);
}

void Tank::SetOrientation()
{
    int x, y, angle;
    x = (double) qrand()/(double) RAND_MAX * (800-50);
    y = (double) qrand()/(double) RAND_MAX * (800-50);
    angle = (double) qrand()/(double) RAND_MAX * 360;
    SetOrientation(x, y, angle);
}

unsigned char Tank::Action()
{
    return action;
}

void Tank::SetAction(unsigned char action)
{
    this->action = action;
}

bool Tank::SendValue()
{
    return send_value;
}

void Tank::setSendValue(bool can_send)
{
    send_value = can_send;
}

void Tank::Fire()
{
    Protocol p(scene);
    action |= Protocol::ACT_FIRE;
    if(!scene->IsServer()) {
        p.SendTankPosition(this, action);
    } else {
        p.GenerateMap();
    }
    action &= ~Protocol::ACT_FIRE;
    if (reload_weapon >= 100) {
        sound_fire->Play(FIRE_SOUND, false);

        Bomb *bomb = new Bomb(scene);
        bomb->SetID(this->id);
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
        reload_weapon = 0;
        progress_reload_weapon->SetProgress(0);
        time_load_weapon->start();
    } else {
        reload_weapon = 0;
    }
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

void Tank::HitByBomb(Bomb *bomb)
{
    if(bomb) {
        if(bomb->ID() != this->id) {
            life-=10;
            progress->SetProgress((qreal) life/ 100.0);
            delete bomb;
            if(life <= 0)
                Died();
        }
    }
}

void Tank::Died()
{
    sound_explosion->Play(false);
    setPixmap(QPixmap(TANK_DEAD_IMAGE).scaled(QSize(80,80),
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));  //imagem do tanque;
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);   //define o ponto de rotação
}

void Tank::timerEvent(QTimerEvent *e)
{
    if(direction==0 && forward==false) {
        if(sound_drive->IsPlaying())
            sound_drive->Stop();
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
        if(!sound_drive->IsPlaying())
            sound_drive->Play(true);
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
    RefactorPosition();
}

void Tank::RefactorPosition()
{
    if(x() + pixmap().width()/2 < 0)
        setX(-pixmap().width()/2);
    if(x() + pixmap().width()/2 > 800)
        setX(800 - pixmap().width()/2);
    if(y() + pixmap().height()/2 < 0)
        setY(-pixmap().height()/2);
    if(y() + pixmap().height()/2 > 800)
        setY(800 - pixmap().height()/2);
}

void Tank::IncrementWeapon()
{
    reload_weapon++;
    progress_reload_weapon->SetProgress(static_cast<qreal>(reload_weapon) / qreal(100.0));
    if(reload_weapon>=100) {
        time_load_weapon->stop();
    }
}
