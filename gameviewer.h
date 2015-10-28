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
private:
    SceneGame *sc_game;
    QRect geometry;
    bool fullscreen;
};

#endif // GAMEVIEWER_H
