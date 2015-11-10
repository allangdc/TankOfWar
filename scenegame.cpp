#include "scenegame.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <iostream>

#include "progressbar.h"
#include "tankcontrolleft.h"
#include "tankcontrolright.h"
#include "tankcontrolforward.h"
#include "tankcontrolfire.h"

SceneGame::SceneGame() : QGraphicsScene()
{
}

void SceneGame::LoadObjects()
{
    Tank *t1 = new Tank(this);
    addItem(t1);
    tanks.push_back(t1);

    Tank *t2 = new Tank(this);
    addItem(t2);
    tanks.push_back(t2);

    t2->SetOrientation(50,50, 180);
    t1->SetOrientation(250,250, 0);

    const int space = 30;

    TankControlLeft *bleft = new TankControlLeft(t1);
    bleft->setPos(space, this->height()-bleft->Size().height()-space);
    addItem(bleft);
    tank_buttons.push_back(bleft);

    TankControlRight *bright = new TankControlRight(t1);
    bright->setPos(this->width() - bright->Size().width() - space, this->height()-bright->Size().height()-space);
    addItem(bright);
    tank_buttons.push_back(bright);

    TankControlForward *bforward = new TankControlForward(t1);
    bforward->setPos(this->width()/2 - bforward->Size().width()/2, this->height()-bforward->Size().height()-space);
    addItem(bforward);
    tank_buttons.push_back(bforward);

    TankControlFire *bfire = new TankControlFire(t1);
    bfire->setPos(this->width() - bfire->Size().width() - space, this->height()-2.2*bfire->Size().height()-space);
    addItem(bfire);
    tank_buttons.push_back(bfire);
}

void SceneGame::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }

    if(event->key() == Qt::Key_Back || event->key() == Qt::Key_Q)
        WantClose();

    if(event->key() == Qt::Key_Left)
        tank_buttons.at(0)->Click(true);
    if(event->key() == Qt::Key_Right)
        tank_buttons.at(1)->Click(true);
    if(event->key() == Qt::Key_Up)
        tank_buttons.at(2)->Click(true);
    if(event->key() == Qt::Key_Space)
        tank_buttons.at(3)->Click(true);
}

void SceneGame::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        return;
    }

    if(event->key() == Qt::Key_Left)
        tank_buttons.at(0)->Click(false);
    if(event->key() == Qt::Key_Right)
        tank_buttons.at(1)->Click(false);
    if(event->key() == Qt::Key_Up)
        tank_buttons.at(2)->Click(false);
    if(event->key() == Qt::Key_Space)
        tank_buttons.at(3)->Click(false);

}

void SceneGame::WantClose()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(NULL, "TankOfWar", "Deseja Sair?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      QApplication::quit();
    }
}

