#include "protocol.h"
#include <QDebug>

Protocol::Protocol(SceneGame *scene)
{
    this->scene = scene;
}

unsigned char Protocol::GetCode(QByteArray array)
{
    unsigned char code = (unsigned char) array.at(0);
    return code;
}


void Protocol::GenerateMap()
{
    struct PTankMap pmap;
    for(int i=0; i<scene->NumTankOnGame(); i++) {
        struct PTankData *ptdata = &(pmap.tanks[i]);
        Tank *tank = scene->getTank(i);
        ptdata->x = tank->pos().x();
        ptdata->y = tank->pos().y();
        ptdata->angle = tank->rotation();
        ptdata->id = i;
        ptdata->fire_on = tank->Action() & ACT_FIRE?1:0;
        if(tank->Action() & ACT_FIRE) {
            int x=0;
        }
        ptdata->move_up = tank->Action() & MOVE_UP?1:0;
        ptdata->move_left = tank->Action() & MOVE_LEFT?1:0;
        ptdata->move_right = tank->Action() & MOVE_RIGHT?1:0;
    }
    pmap.code = SEND_MAP;
    pmap.total_tank = scene->NumTankOnGame();

    const char *ch = (const char *) &pmap;
    QByteArray array(ch, sizeof(struct PTankMap));
    scene->gserver->BroadcastMessage(array);
}

void Protocol::ReceiveMap(QByteArray array)
{
    struct PTankMap *pmap;
    pmap = (struct PTankMap *) array.data();
    for(int i=0; i<pmap->total_tank; i++) {
        struct PTankData *ptdata;
        ptdata = &(pmap->tanks[i]);
        if(pmap->total_tank > scene->NumTankOnGame()) {
            scene->CreateTank(QPointF(ptdata->x, ptdata->y),
                       ptdata->angle);
        } else {
            if(ptdata->id != scene->id_tank) {
                Tank *t = scene->getTank(i);
                t->setPos(ptdata->x, ptdata->y);
                t->setRotation(ptdata->angle);

                if(ptdata->move_up == 1) {
                    t->MoveFoward(true);
                } else {
                    t->MoveFoward(false);
                }

                if(ptdata->move_right == 1) {
                    t->RotateRight(true);
                } else {
                    t->RotateRight(false);
                }

                if(ptdata->move_left == 1) {
                    t->RotateLeft(true);
                } else {
                    t->RotateLeft(false);
                }
                if(ptdata->fire_on == 1) {
                    t->Fire();
                }

            }
        }
    }
    if(!scene->HasControl()) {
        scene->CreateControls(pmap->total_tank-1);
    }
}

void Protocol::SendTankPosition(Tank *tank, unsigned char action)
{
    if(action & ACT_FIRE) {
        int x=0;
    }
    static int i=0;
    if (tank->SendValue()) {
        qDebug() << "Send " << i++;
        struct PTankData data;
        data.code = SEND_TANK_POSITION;
        data.x = tank->pos().x();
        data.y = tank->pos().y();
        data.send_value = 1;
        data.angle = tank->rotation();
        data.id = scene->id_tank;
        data.fire_on = action & ACT_FIRE?1:0;
        data.move_up = action & MOVE_UP?1:0;
        data.move_left = action & MOVE_LEFT?1:0;
        data.move_right = action & MOVE_RIGHT?1:0;
        const char *ch = (const char *) &data;
        QByteArray array(ch, sizeof(struct PTankData));
        scene->gclient->SendMessage(array);
    }
}

void Protocol::ReceiveTankPosition(QByteArray array)
{
    struct PTankData *data;
    data = (struct PTankData *) array.data();
    Tank* t = scene->getTank(data->id);
    t->setPos(data->x, data->y);
    t->setRotation(data->angle);
    t->setSendValue(false);

    if(data->move_up == 1) {
        t->MoveFoward(true);
    } else {
        t->MoveFoward(false);
    }

    if(data->move_right == 1) {
        t->RotateRight(true);
    } else {
        t->RotateRight(false);
    }

    if(data->move_left == 1) {
        t->RotateLeft(true);
    } else {
        t->RotateLeft(false);
    }

    if(data->fire_on == 1) {
        t->Fire();
    }
}


