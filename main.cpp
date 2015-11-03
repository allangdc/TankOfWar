#include <QApplication>

#include "gameviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef __ANDROID__
    GameViewer game(true);
#else
    GameViewer game;
#endif
    game.show();

    return a.exec();
}
