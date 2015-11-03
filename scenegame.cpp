#include "scenegame.h"

#include <QKeyEvent>
#include <QObject>
#include <QDebug>''
#include <iostream>

#include "tankcontrolbutton.h"
#include "tankcontrolleft.h"

SceneGame::SceneGame()
{

}

void SceneGame::MoveTank(unsigned char action)
{
    Tank *tank = tanks.at(id_tank);

    unsigned char aux = action & GO_STOP;


    bool run = aux==(unsigned char)GO_STOP?false:true;
    std::cout << "run=" << run << std::endl;

    aux = action & GO_FORWARD;
    if(aux == (unsigned char) GO_FORWARD)
        tank->MoveFoward(run);
    if((aux=action & GO_LEFT) == GO_LEFT)
        tank->RotateLeft(run);
    if((aux=action & GO_RIGHT) == GO_RIGHT)
        tank->RotateRight(run);
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

    const int space = 30;

    TankControlLeft *bleft = new TankControlLeft(t1);
    bleft->move(space, this->height()-bleft->size().height()-space);
    bleft->setText("<<");
    addWidget(bleft);

    TankControlButton *bright = new TankControlButton(t1);
    bright->move(this->width() - bright->size().width() - space, this->height()-bright->size().height()-space);
    bright->setText(">>");
    addWidget(bright);

    TankControlButton *bforward = new TankControlButton(t1);
    bforward->move(this->width()/2 - bforward->size().width()/2, this->height()-bforward->size().height()-space);
    bforward->setText("|");
    addWidget(bforward);
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

