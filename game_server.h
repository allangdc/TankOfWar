#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QVector>
#include <QMutex>

class GameSocket;

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = 0);
    void ReadReady(int id, QByteArray data);
    void SendMessage(int id, QByteArray data);
private:
    QVector<GameSocket *> sockets;
    QMutex mutex;
signals:

public slots:
    void NewConnection();
};

#endif // GAMESERVER_H