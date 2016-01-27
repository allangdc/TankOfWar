#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPoint>

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

class SceneGame;
class ProgressBar;
class Sound;
class Bomb;

class Tank: public QTimer, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tank(SceneGame *scene);
    Tank(SceneGame *scene, QPointF position, qreal angle);
    virtual ~Tank();
    void RotateLeft(bool run=true);
    void RotateRight(bool run=true);
    void MoveFoward(bool run=true);
    void MoveStop();
    void SetOrientation(QPoint position, double angle);
    void SetOrientation(qreal x, qreal y, qreal angle);
    void SetOrientation();
    unsigned char Action();
    void SetAction(unsigned char action);
    bool SendValue();
    void setSendValue(bool can_send);
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
    void RefactorPosition();
private:
    int id;
    int direction;
    bool forward;
    bool send_value;
    unsigned char action;
    SceneGame *scene;
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
