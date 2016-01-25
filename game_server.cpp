#include "game_server.h"
#include "game_socket.h"

#include <QDebug>
#include <QTcpSocket>

GameServer::GameServer(QObject *parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(NewConnection()));

    if(listen(QHostAddress::Any, 9999)) {
        qDebug() << "Server Started!";
    } else {
        qDebug() << "Server could not start!";
    }
}

void GameServer::ReadReady(int id, QByteArray data)
{
    QMutexLocker lock(&mutex);

    qDebug() << "SERVER->" << QString("socket[%1] =").arg(id) << data;
    emit ReceiverMSG(id, data);
}

void GameServer::SendMessage(int id, QByteArray data)
{
    QMutexLocker lock(&mutex);
    qDebug() << "SendMessage";
    for(QVector<GameSocket *>::iterator it = sockets.begin();
                                        it != sockets.end();
                                        it++) {
        GameSocket *game_socket = *it;
        if(game_socket->ID() == id) {
            QTcpSocket *socket = game_socket->getSocket();
            socket->write(data);
            socket->flush();
            socket->waitForBytesWritten();
            return;
        }
    }
}

void GameServer::BroadcastMessage(QByteArray data)
{
    QMutexLocker lock(&mutex);
    qDebug() << "BroadcastMessage";
    for(QVector<GameSocket *>::iterator it = sockets.begin();
                                        it != sockets.end();
                                        it++) {
        GameSocket *game_socket = *it;
        QTcpSocket *socket = game_socket->getSocket();
        socket->write(data);
        socket->flush();
        socket->waitForBytesWritten();
    }
}


void GameServer::NewConnection()
{
    QMutexLocker lock(&mutex);
    static int i = 0;
    GameSocket *game_socket = new GameSocket(nextPendingConnection());
    sockets.push_back(game_socket);
    QTcpSocket *socket = game_socket->getSocket();
    game_socket->setID(++i);
    game_socket->setServer(this);

//    socket->write("Hello guy\n");
//    socket->flush();
//    socket->waitForBytesWritten(3000);

    emit InitConnection(game_socket->ID());
}

