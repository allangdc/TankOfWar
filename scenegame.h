#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <QGraphicsScene>
#include <QVector>
#include <QTimer>
#include "tank.h"

class Button;

class SceneGame: public QGraphicsScene
{
public:
    SceneGame();
    void MoveTank(int action);
    void LoadObjects();
protected:
    int id_tank=0;
    void keyPressEvent(QKeyEvent *e);
    QVector<Tank *> tanks;
    Button *btn_left, *btn_right, *btn_forward;
    QTimer *timer_tank;
};

#endif // SCENEGAME_H
