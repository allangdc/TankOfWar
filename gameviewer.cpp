#include "gameviewer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>

GameViewer::GameViewer(bool fullscreen): QGraphicsView()
{
    this->fullscreen = fullscreen;
    sc_game = new SceneGame();
    this->setScene(sc_game);
    if(!fullscreen) {
        geometry = QRect(0,0,300,400);
    } else {
        geometry = QApplication::desktop()->screenGeometry();
    }
    setGeometry(geometry);
    setSceneRect(geometry);
    sc_game->setSceneRect(geometry);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sc_game->LoadObjects();
}

void GameViewer::show()
{
    if(!fullscreen) {
        QGraphicsView::show();
    } else {
        QGraphicsView::showFullScreen();
    }
}

