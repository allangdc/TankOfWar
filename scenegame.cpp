#include "scenegame.h"

#include <QKeyEvent>
#include <QObject>

#include "buttonleft.h"
#include "buttonright.h"

SceneGame::SceneGame()
{

}

void SceneGame::MoveTank(int action)
{
    Tank *tank = tanks.at(id_tank);
    switch (action) {
    case GO_LEFT:
        tank->RotateLeft();
        break;
    case GO_RIGHT:
        tank->RotateRight();
        break;
    case GO_FORWARD:
        tank->MoveFoward();
        break;
    case STOP:
        tank->MoveStop();
        break;
    default:
        break;
    }
}

void SceneGame::LoadObjects()
{
    Tank *t1 = new Tank();
    addItem(t1);
    tanks.push_back(t1);

    Tank *t2 = new Tank();
    addItem(t2);
    tanks.push_back(t2);

    t2->SetOrientation(50,50, 180);
    t1->SetOrientation(250,250, 0);

    btn_left = new ButtonLeft(this);
    addItem(btn_left);
    btn_left->setPos(0, this->height()-btn_left->Size().height());

    btn_right = new ButtonRight(this);
    addItem(btn_right);
    btn_right->setPos(this->width() - btn_right->Size().width(), this->height()-btn_left->Size().height());
}

void SceneGame::keyPressEvent(QKeyEvent *e)
{
    Tank *tank = tanks.at(1);
    switch(e->key()) {
    case Qt::Key_Left:
        tank->RotateLeft();
        break;
    case Qt::Key_Right:
        tank->RotateRight();
        break;
    case Qt::Key_Up:
        tank->MoveFoward();
        break;
    }
}

