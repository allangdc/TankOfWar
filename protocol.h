#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QByteArray>

#include "scenegame.h"
#include "tank.h"

struct CId {
    unsigned char code;
    unsigned char id;
};

struct CCreateTank {
    unsigned char code;
    qreal x;
    qreal y;
    qreal angle;
};

struct CTankAction {
    unsigned char code;
    unsigned char tank_id;
    unsigned char left: 1;
    unsigned char right: 1;
    unsigned char up: 1;
    unsigned char fire: 1;
};

class Protocol
{
public:
    enum msg_list {
        CREATE_TANK,
        TANK_ACTION,
        ID
    };
    Protocol(SceneGame *scene);
    static unsigned char GetCode(QByteArray array);

    QByteArray CreateTank(qreal x, qreal y, qreal angle);
    QByteArray TankAction(unsigned char tank_id, bool left, bool right, bool up, bool fire);
    QByteArray SetID(unsigned char id);
    CCreateTank GetCCreateTank(QByteArray array);
    CTankAction GetCTankAction(QByteArray array);
    CId GetID(QByteArray array);
private:
    SceneGame *scene;
};

#endif // PROTOCOL_H
