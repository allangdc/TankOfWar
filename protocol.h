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
    unsigned char id;
    unsigned char send_value: 1;
    unsigned char fire_on   : 1;
    unsigned char move_up   : 1;
    unsigned char move_left : 1;
    unsigned char move_right: 1;
};

struct PTankMap {
    unsigned char code;
    struct PTankData tanks[5];
    unsigned char total_tank;
};

class Protocol
{
public:
    enum msg_list {
        SEND_MAP,
        SEND_TANK_POSITION
    };
    enum direction {
        MOVE_STOP    = 0b0000,
        MOVE_LEFT    = 0b0001,
        MOVE_RIGHT   = 0b0010,
        MOVE_UP      = 0b0100,
        ACT_FIRE     = 0b1000
    };
    Protocol(SceneGame *scene);
    static unsigned char GetCode(QByteArray array);

    void GenerateMap();
    void ReceiveMap(QByteArray array);
    void SendTankPosition(Tank *tank, unsigned char action);
    void ReceiveTankPosition(QByteArray array);
private:
    SceneGame *scene;
};

#endif // PROTOCOL_H

