#include "buttonright.h"

ButtonRight::ButtonRight(SceneGame *scene): Button(scene)
{
    setRotation(-90);
}

void ButtonRight::ClickOn()
{
    ((SceneGame *) scene)->MoveTank(GO_RIGHT);
}

void ButtonRight::ClickOff()
{
    ((SceneGame *) scene)->MoveTank(STOP);
}

