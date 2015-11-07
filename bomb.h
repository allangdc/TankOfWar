#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPoint>

#define STEP        10.0
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
