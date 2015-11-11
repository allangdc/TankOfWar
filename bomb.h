#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPoint>

#define VELOCITY_BOMB   300.0f //pixel/sec
#define FRAME_BOMB      60.0f
#define STEP_BOMB       VELOCITY_BOMB/FRAME_BOMB
#define BOMB_IMAGE  ":/Image/bombs/image/ball01.png"

class QGraphicsScene;

class Bomb : public QGraphicsPixmapItem, public QTimer
{
public:
    Bomb(QGraphicsScene *scene);
    Bomb(QGraphicsScene *scene, QPointF position, qreal angle);
    void Fire();
    void SetAngle(qreal angle);
private:
    void timerEvent(QTimerEvent *e);
    void PulseForward();
    QGraphicsScene *scene;
};

#endif // BOMB_H
