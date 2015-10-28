#include <QApplication>

#include "gameviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameViewer game(true);
    game.show();

    return a.exec();
}
