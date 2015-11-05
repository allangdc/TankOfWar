#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <QGraphicsScene>
#include <QVector>
#include "tank.h"
#include "tankcontrolbutton.h"

class TankControlLeft;
class TankControlRight;
class TankControlForward;

class SceneGame: public QGraphicsScene
{
public:
    SceneGame();
    void MoveTank(unsigned char action);
    void LoadObjects();
protected:
    int id_tank=0;
    void keyPressEvent(QKeyEvent *e);
    bool event(QEvent *event);
    QVector<Tank *> tanks;
    QVector<TankControlButton *> tank_buttons;
};

#endif // SCENEGAME_H
