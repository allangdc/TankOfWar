#include "game_client.h"

#include <QDebug>

GameClient::GameClient(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

void GameClient::ReadyRead()
{
    QByteArray data = this->readAll();
    qDebug() << "ALLAN: " << data;
}

