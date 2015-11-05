#include "scenegame.h"

#include <QKeyEvent>
#include <QObject>
#include <QDebug>''
#include <iostream>

#include "tankcontrolbutton.h"
#include "tankcontrolleft.h"
#include "tankcontrolright.h"
#include "tankcontrolforward.h"
#include <QTouchEvent>

SceneGame::SceneGame()
{

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
    addWidget(bleft);
    tank_buttons.push_back(bleft);

    TankControlRight *bright = new TankControlRight(t1);
    bright->move(this->width() - bright->size().width() - space, this->height()-bright->size().height()-space);
    addWidget(bright);
    tank_buttons.push_back(bright);

    TankControlForward *bforward = new TankControlForward(t1);
    bforward->move(this->width()/2 - bforward->size().width()/2, this->height()-bforward->size().height()-space);
    addWidget(bforward);
    tank_buttons.push_back(bforward);
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

bool SceneGame::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QList<QTouchEvent::TouchPoint> pts = static_cast<QTouchEvent *>(event)->touchPoints();
        for(QList<QTouchEvent::TouchPoint>::iterator it=pts.begin(); it != pts.end(); it++) {
            QRectF rectf = it->rect();
            if (rectf.isEmpty()) {
                qreal diameter = qreal(50) * it->pressure();
                rectf.setSize(QSizeF(diameter, diameter));
            }
            QRect rect = rectf.toRect();

            switch(it->state()) {
                case Qt::TouchPointStationary:
                    continue;
                case Qt::TouchPointReleased:
                    if(!rect.intersected(tank_buttons.at(0)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateLeft(false);
                    } else if(!rect.intersected(tank_buttons.at(1)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateRight(false);
                    } else if(!rect.intersected(tank_buttons.at(2)->geometry()).isEmpty()) {
                        tanks.at(0)->MoveFoward(false);
                    }
                    break;
                case Qt::TouchPointMoved:
                    if(!rect.intersected(tank_buttons.at(0)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateLeft(true);
                    } else if(!rect.intersected(tank_buttons.at(1)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateRight(true);
                    } else if(!rect.intersected(tank_buttons.at(2)->geometry()).isEmpty()) {
                        tanks.at(0)->MoveFoward(true);
                    } else {
                        tanks.at(0)->MoveStop();
                    }
                    break;
                default:
                    if(!rect.intersected(tank_buttons.at(0)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateLeft(true);
                    } else if(!rect.intersected(tank_buttons.at(1)->geometry()).isEmpty()) {
                        tanks.at(0)->RotateRight(true);
                    } else if(!rect.intersected(tank_buttons.at(2)->geometry()).isEmpty()) {
                        tanks.at(0)->MoveFoward(true);
                    }
                    break;
            }
        }
        break;
    }
    default:
        return QGraphicsScene::event(event);
    }
    return true;
}

