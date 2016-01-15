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
protected:
    int id_tank=0;
    QVector<Tank *> tanks;
    QVector<TankControlButton *> tank_buttons;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void WantClose();
    GameViewer *view;

    GameServer *gserver;
    GameClient *gclient;

public slots:
    void ServerInitConnection(int id);
    void ServerReceiveMSG(int id, QByteArray array);
    void ClientReceiveMSG(QByteArray array);
private:
    Tank *CreateTank();
    void CreateControls(Tank *t);
};

#endif // SCENEGAME_H
