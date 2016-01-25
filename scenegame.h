#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <QGraphicsScene>
#include <QVector>
#include <QEvent>

#include "tank.h"
#include "tankcontrolbutton.h"

#include "game_server.h"
#include "game_client.h"

class TankControlLeft;
class TankControlRight;
class TankControlForward;
class GameViewer;

class SceneGame: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGame(GameViewer *view = NULL);
    ~SceneGame();
    void MoveTank(unsigned char action);
    void LoadObjects();
    void InitServer();

    Tank *CreateTank();
    Tank *CreateTank(QPointF position, qreal angle);
    void CreateControls(Tank *t);
    void CreateControls(int id);
    Tank *getTank(int id);
    int NumTankOnGame();
    bool HasControl();

    //Server commands
    void ServerSendMap();
    void ServerSendID();

    //Clients commands
    void ClientGetMap(QByteArray array);


    GameServer *gserver;
    GameClient *gclient;
    int id_tank=0;
    bool IsServer();
protected:
    QVector<Tank *> tanks;
    QVector<TankControlButton *> tank_buttons;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void WantClose();
    GameViewer *view;

    qreal scale;
    bool block_command=false;

public slots:
    void ServerInitConnection(int id);
    void ServerReceiveMSG(int id, QByteArray array);
    void ClientReceiveMSG(QByteArray array);
};

#endif // SCENEGAME_H

