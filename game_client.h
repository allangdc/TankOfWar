#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QTcpSocket>
#include "game_socket.h"

class GameClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
private:

signals:
    void ReceiverMSG(QByteArray array);

public slots:
    void ReadyRead();
};

#endif // GAMECLIENT_H
