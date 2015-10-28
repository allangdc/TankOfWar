#ifndef BUTTONLEFT_H
#define BUTTONLEFT_H

#include "button.h"
#include "scenegame.h"

class ButtonLeft: public Button
{
public:
    ButtonLeft(SceneGame *scene);
    void ClickOn();
    void ClickOff();
};

#endif // BUTTONLEFT_H
