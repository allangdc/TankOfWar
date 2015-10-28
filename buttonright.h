#ifndef BUTTONRIGHT_H
#define BUTTONRIGHT_H

#include "button.h"
#include "scenegame.h"

class ButtonRight: public Button
{
public:
    ButtonRight(SceneGame *scene);
    void ClickOn();
    void ClickOff();
};

#endif // BUTTONRIGHT_H
