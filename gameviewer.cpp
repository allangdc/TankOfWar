#include "gameviewer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QTouchEvent>
#include <QKeyEvent>

GameViewer::GameViewer(bool fullscreen): QGraphicsView()
{
    this->fullscreen = fullscreen;
    sc_game = new SceneGame();
    this->setScene(sc_game);
    if(!fullscreen) {
        geometry = QRect(0,0,526,701);
    } else {
        geometry = QApplication::desktop()->screenGeometry();
    }
    setGeometry(geometry);
    setSceneRect(geometry);
    sc_game->setSceneRect(geometry);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sc_game->LoadObjects();
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
}

void GameViewer::show()
{
    if(!fullscreen) {
        QGraphicsView::show();
    } else {
        QGraphicsView::showFullScreen();
    }
}
