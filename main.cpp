#include <QApplication>

#include "gameviewer.h"
#include "login.h"

#include "game_server.h"
#include "game_client.h"

#include <QNetworkInterface>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef __ANDROID__
    GameViewer game(true);
#else
    GameViewer game;
#endif

    Login *login = new Login(&game);
    int ret = login->exec();
    delete login;

    if(ret == QDialog::Accepted)
        game.show();
    else
        return 0;


    return a.exec();
}
