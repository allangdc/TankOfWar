#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <QGraphicsScene>
#include <QVector>
#include <QEvent>

#include "tank.h"
#include "tankcontrolbutton.h"

class TankControlLeft;
class TankControlRight;
class TankControlForward;

class SceneGame: public QGraphicsScene
{
public:
    explicit SceneGame(QGraphicsView *view = NULL);
    void MoveTank(unsigned char action);
    void LoadObjects();
protected:
    int id_tank=0;
    QVector<Tank *> tanks;
    QVector<TankControlButton *> tank_buttons;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void WantClose();
    QGraphicsView *view;
};

#endif // SCENEGAME_H
