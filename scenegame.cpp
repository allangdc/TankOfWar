#include "scenegame.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDesktopWidget>

#include "gameviewer.h"
#include "game_socket.h"
#include "protocol.h"

#include "progressbar.h"
#include "tankcontrolleft.h"
#include "tankcontrolright.h"
#include "tankcontrolforward.h"
#include "tankcontrolfire.h"

SceneGame::SceneGame(GameViewer *view) : QGraphicsScene()
{
    this->view = view;
    gserver = NULL;
    gclient = NULL;
}

SceneGame::~SceneGame()
{
    if(gserver)
        delete gserver;
    if(gclient)
        delete gclient;
}

void SceneGame::InitServer()
{
    if(view->IsServer()) {
        gserver = new GameServer();
        connect(gserver, SIGNAL(InitConnection(int)), this, SLOT(ServerInitConnection(int)));
        connect(gserver, SIGNAL(ReceiverMSG(int,QByteArray)), SLOT(ServerReceiveMSG(int,QByteArray)));
        Tank *t = CreateTank();
        CreateControls(t);
    } else {
        gclient = new GameClient();
        connect(gclient, SIGNAL(ReceiverMSG(QByteArray)), this, SLOT(ClientReceiveMSG(QByteArray)));
        gclient->connectToHost(view->IP(), 9999);
        gclient->waitForConnected();
        gclient->write("Conectei");
    }
}

void SceneGame::LoadObjects()
{   
    float scale = view->width() / this->width();
    this->view->scale(scale, scale);

    QGraphicsTextItem *info = new QGraphicsTextItem();
    QString msg = "Type: ";
    if(view->IsServer())
        msg += "Server";
    else
        msg += "Client";
    msg += " | IP: ";
    msg += view->IP();
    info->setHtml(msg);
    this->addItem(info);
    info->setPos(0, -30);

    QGraphicsRectItem *rect = new QGraphicsRectItem(QRect(0,0,800,800));
    this->addItem(rect);
    QGraphicsLineItem *line = new QGraphicsLineItem(400,0, 400, 800);
    this->addItem(line);

//    Tank *t1 = new Tank(this);
//    addItem(t1);
//    tanks.push_back(t1);

//    Tank *t2 = new Tank(this);
//    addItem(t2);
//    tanks.push_back(t2);

//    t2->SetOrientation(50,50, 180);
//    t1->SetOrientation(250,250, 0);

//    Tank *t1 = CreateTank();

//    CreateControls(t1);
}

void SceneGame::CreateControls(Tank *t)
{
    float scale = view->width() / this->width();
    const float space = 20.0;
    QPointF ptf;

    TankControlLeft *bleft = new TankControlLeft(t);
    ptf = QPointF(space/scale,
                  view->height()-bleft->Size().height()*scale-space/scale);
    bleft->setPos(view->mapToScene(ptf.toPoint()));
    addItem(bleft);
    tank_buttons.push_back(bleft);

    TankControlRight *bright = new TankControlRight(t);
    ptf = QPointF(view->width() - bright->Size().width()*scale - space/scale,
                  view->height()-bright->Size().height()*scale-space/scale);
    bright->setPos(view->mapToScene(ptf.toPoint()));
    addItem(bright);
    tank_buttons.push_back(bright);

    TankControlForward *bforward = new TankControlForward(t);
    ptf = QPointF(view->width()/2 - bforward->Size().width()*scale/2,
                  view->height() - bforward->Size().height()*scale - space/scale);
    bforward->setPos(view->mapToScene(ptf.toPoint()));
    addItem(bforward);
    tank_buttons.push_back(bforward);

    TankControlFire *bfire = new TankControlFire(t);
    ptf = QPointF(view->width() - bfire->Size().width()*scale - space/scale,
                  view->height() - 2*scale*(bfire->Size().height()/scale + space/scale) );
    bfire->setPos(view->mapToScene(ptf.toPoint()));
    addItem(bfire);
    tank_buttons.push_back(bfire);

    for(QVector<TankControlButton *>::iterator it=tank_buttons.begin(); it != tank_buttons.end(); it++)
    {
        TankControlButton *tc = *it;
#ifdef __ANDROID__
        tc->setScale(1/scale);
#else
        tc->setVisible(false);
#endif
    }
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

void SceneGame::ServerInitConnection(int id)
{
    Tank *t1 = CreateTank();
    t1->SetOrientation();
    QByteArray array = Protocol::CreateTank(t1->x(), t1->y(), t1->rotation());
    gserver->BroadcastMessage(array);
}

void SceneGame::ServerReceiveMSG(int id, QByteArray array)
{

}

void SceneGame::ClientReceiveMSG(QByteArray array)
{
    CCreateTank cct;
    Tank *t;

    switch (Protocol::GetCode(array)) {
        case Protocol::CREATE_TANK:
            cct = Protocol::GetCCreateTank(array);
            t = new Tank(this, QPoint(cct.x, cct.y), cct.angle);
        break;
    }
}

Tank *SceneGame::CreateTank()
{
    Tank *t = new Tank(this);
    addItem(t);
    tanks.push_back(t);

    t->SetOrientation();

    return t;
}

