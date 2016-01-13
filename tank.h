#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>

#define VELOCITY_TANK       100.0f //pixel/sec
#define FRAME_TANK          60
#define STEP_TANK           VELOCITY_TANK/FRAME_TANK

#define TANK_IMAGE          ":/image/tank/image/yellow.png"
#define TANK_DEAD_IMAGE     ":/image/tank/image/red.png"

#define FIRE_SOUND          ":/Sounds/Fire/sounds/TankFire01.wav"
#define DRIVE_TANK_SOUND    ":/Sounds/Fire/sounds/TankMove02.wav"
#define EXPLOSION_SOUND     ":/Sounds/Fire/sounds/Explosion01.wav"

enum {
    STOP        = 0b00000000,   // 0
    GO_FORWARD  = 0b00000001,   // 1
    GO_LEFT     = 0b00000010,   // 2
    GO_RIGHT    = 0b00000100,   // 3
    GO_STOP     = 0b10000000    //
};

class QGraphicsScene;
class ProgressBar;
class Sound;
class Bomb;

class Tank: public QTimer, public QGraphicsPixmapItem
{
    Q_OBJECT
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
    void HitByBomb(Bomb *bomb);
    void Died();
protected:
    void timerEvent(QTimerEvent *e);
    void PulseLeft();
    void PulseRight();
    void PulseForward();
private:
    int id;
    int direction;
    bool forward;
    QGraphicsScene *scene;
    ProgressBar *progress;
    ProgressBar *progress_reload_weapon;
    int life;
    int reload_weapon;
    Sound *sound_fire;
    Sound *sound_drive;
    Sound *sound_explosion;
    QTimer *time_load_weapon;
public slots:
    void IncrementWeapon();
};

#endif // TANK_H
