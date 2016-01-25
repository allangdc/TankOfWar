#include "gameviewer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QTouchEvent>
#include <QKeyEvent>

#include <unistd.h>

GameViewer::GameViewer(bool fullscreen): QGraphicsView()
{
    this->fullscreen = fullscreen;

    sc_game = new SceneGame(this);
    this->setScene(sc_game);
    if(!fullscreen) {
        geometry = QRect(0,0,526,701);
    } else {
        geometry = QApplication::desktop()->screenGeometry();
    }
    setGeometry(geometry);
    setSceneRect(QRect(0,0, 800, 800));
    sc_game->setSceneRect(QRect(0,0, 800, 800));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
}

void GameViewer::show()
{
    sc_game->LoadObjects();
    sc_game->InitServer();

    if(!fullscreen) {
        QGraphicsView::show();
    } else {
        QGraphicsView::showFullScreen();
    }
}

void GameViewer::setIP(bool is_server, QString ip_connect, QString port)
{
    this->is_server = is_server;
    this->ipserver = ip_connect;
    this->port = port.toInt();
}

QString GameViewer::IP()
{
    return ipserver;
}

bool GameViewer::IsServer()
{
    return is_server;
}

int GameViewer::Port()
{
    return port;
}
