#ifndef GAMEVIEWER_H
#define GAMEVIEWER_H

#include <QGraphicsView>
#include <QRect>
#include "scenegame.h"

class GameViewer: public QGraphicsView
{
public:
    GameViewer(bool fullscreen=false);
    void show();
    void setIP(bool is_server, QString ip_connect);
    QString IP();
    bool IsServer();
protected:
    //void keyPressEvent(QKeyEvent *event);
private:
    SceneGame *sc_game;
    QRect geometry;
    bool fullscreen;
    bool is_server;
    QString ipserver;
};

#endif // GAMEVIEWER_H
