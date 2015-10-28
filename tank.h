#ifndef TANK_H
#define TANK_H

#include <QGraphicsPixmapItem>
#include <QTimer>

#define STEP    3.0

enum {
    STOP, GO_FORWARD, GO_LEFT, GO_RIGHT
};

class Tank: public QGraphicsPixmapItem, public QTimer
{
public:
    Tank();
    void RotateLeft();
    void RotateRight();
    void MoveFoward();
    void MoveStop();
    void SetOrientation(QPoint position, double angle);
    void SetOrientation(int x, int y, double angle);
protected:
    void timerEvent(QTimerEvent *e);
    void PulseLeft();
    void PulseRight();
    void PulseForward();
private:
    int action;
};

#endif // TANK_H
