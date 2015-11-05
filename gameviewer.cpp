#include "gameviewer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QTouchEvent>

GameViewer::GameViewer(bool fullscreen): QGraphicsView(), totalScaleFactor(1)
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

//bool GameViewer::viewportEvent(QEvent *event)
//{
//    switch (event->type()) {
//        case QEvent::TouchBegin:
//        case QEvent::TouchUpdate:
//        case QEvent::TouchEnd:
//        {
//            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
//            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
//            if (touchPoints.count() == 2) {
//                // determine scale factor
//                const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
//                const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
//                qreal currentScaleFactor =
//                     QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
//                     / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
//                if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
//                    // if one of the fingers is released, remember the current scale
//                    // factor so that adding another finger later will continue zooming
//                    // by adding new scale factor to the existing remembered value.
//                    totalScaleFactor *= currentScaleFactor;
//                    currentScaleFactor = 1;
//                }
//                setTransform(QTransform().scale(totalScaleFactor * currentScaleFactor,
//                                             totalScaleFactor * currentScaleFactor));
//            }
//            return true;
//        }
//        default:
//        break;
//    }
//    return QGraphicsView::viewportEvent(event);
//}

