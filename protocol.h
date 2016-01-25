#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QByteArray>

#include "scenegame.h"
#include "tank.h"

struct PTankData {
    unsigned char code;
    qreal x;
    qreal y;
    qreal angle;
    bool fire_on;
    unsigned char id;
};

struct PTankMap {
    unsigned char code;
    struct PTankData tanks[5];
    unsigned char total_tank;
};

struct PTankCreateMe {
    unsigned char code;
};

struct PTankID {
    unsigned char code;
    unsigned char id;
};

class Protocol
{
public:
    enum msg_list {
        SEND_MAP,
        CREATE_ME,
        SEND_TANK_POSITION,
        SEND_ID
    };
    Protocol(SceneGame *scene);
    static unsigned char GetCode(QByteArray array);

    void GenerateMap(bool fire_on=false, int id=0);
    void ReceiveMap(QByteArray array);
    void CreateMe();
    void ReceiveCreateMe();
    void SendTankPosition(Tank *tank, bool fire_on=false);
    void ReceiveTankPosition(QByteArray array);
private:
    SceneGame *scene;
};

#endif // PROTOCOL_H
