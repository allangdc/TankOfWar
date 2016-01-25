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


void Protocol::GenerateMap(bool fire_on, int id)
{
    struct PTankMap pmap;
    pmap.code = SEND_MAP;
    pmap.total_tank = scene->NumTankOnGame();
    for(int i=0; i<scene->NumTankOnGame(); i++) {
        struct PTankData *ptdata = &(pmap.tanks[i]);
        Tank *tank = scene->getTank(i);
        ptdata->x = tank->pos().x();
        ptdata->y = tank->pos().y();
        ptdata->angle = tank->rotation();
        ptdata->id = i;
        if(i==id)
            ptdata->fire_on = fire_on;
        else
            ptdata->fire_on = false;
    }
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
                if(ptdata->fire_on) {
                    t->Fire();
                }
            }
        }
    }
    if(!scene->HasControl()) {
        scene->CreateControls(pmap->total_tank-1);
    }
}

void Protocol::CreateMe()
{
    unsigned char code = CREATE_ME;
    QByteArray data((const char *) &code, sizeof(unsigned char));
    scene->gclient->SendMessage(data);
}

void Protocol::ReceiveCreateMe()
{
    Tank *t = scene->CreateTank();
    GenerateMap();
}

void Protocol::SendTankPosition(Tank *tank, bool fire_on)
{
    struct PTankData data;
    data.code = SEND_TANK_POSITION;
    data.x = tank->pos().x();
    data.y = tank->pos().y();
    data.angle = tank->rotation();
    data.id = scene->id_tank;
    data.fire_on = fire_on;
    const char *ch = (const char *) &data;
    QByteArray array(ch, sizeof(struct PTankData));
    scene->gclient->SendMessage(array);
}

void Protocol::ReceiveTankPosition(QByteArray array)
{
    struct PTankData *data;
    data = (struct PTankData *) array.data();
    Tank* t = scene->getTank(data->id);
    t->setPos(data->x, data->y);
    t->setRotation(data->angle);
    if(data->fire_on) {
        t->Fire();
        GenerateMap(true, data->id);
    } else {
        GenerateMap();
    }
}


