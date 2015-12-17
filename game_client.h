#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QTcpSocket>

class GameClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);

public slots:
    void ReadyRead();
};

#endif // GAMECLIENT_H
