#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSound>

#define VELOCITY_TANK       100.0f //pixel/sec
#define FRAME_TANK          60
#define STEP_TANK           VELOCITY_TANK/FRAME_TANK

#define TANK_IMAGE          ":/image/tank/image/yellow.png"
#define FIRE_SOUND          ":/Sounds/Fire/sounds/TankFire01.wav"
#define DRIVE_TANK_SOUND    ":/Sounds/Fire/sounds/TankMove01.wav"

enum {
    STOP        = 0b00000000,   // 0
    GO_FORWARD  = 0b00000001,   // 1
    GO_LEFT     = 0b00000010,   // 2
    GO_RIGHT    = 0b00000100,   // 3
    GO_STOP     = 0b10000000    //
};

class QGraphicsScene;
class ProgressBar;

class Tank: public QGraphicsPixmapItem, public QTimer
{
public:
    Tank(QGraphicsScene *scene);
    virtual ~Tank();
    void RotateLeft(bool run=true);
    void RotateRight(bool run=true);
    void MoveFoward(bool run=true);
    void MoveStop();
    void SetOrientation(QPoint position, double angle);
    void SetOrientation(int x, int y, double angle);
    int Action();
    void MoveAction(int action);
    void Fire();
    void setPos(qreal x, qreal y);
    void setPos(QPointF point);
    void setRotation(qreal angle);
protected:
    void timerEvent(QTimerEvent *e);
    void PulseLeft();
    void PulseRight();
    void PulseForward();
private:
    int direction;
    bool forward;
    QGraphicsScene *scene;
    ProgressBar *progress;
    int life;
    QSound *sound_fire;
    QSound *sound_drive;
};

#endif // TANK_H
