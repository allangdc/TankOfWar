#include "buttonleft.h"

ButtonLeft::ButtonLeft(SceneGame *scene): Button(scene)
{
    setRotation(90);
}

void ButtonLeft::ClickOn()
{
    ((SceneGame *) scene)->MoveTank(GO_LEFT);
}

void ButtonLeft::ClickOff()
{
    ((SceneGame *) scene)->MoveTank(STOP);
}



