#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "gameviewer.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(GameViewer *game_viewer);
    ~Login();

public slots:
    void OnOkClick();
    void OnCancelClick();

private:
    Ui::Login *ui;
    GameViewer *gviewer;
};

#endif // LOGIN_H
