
#pragma once

#include "Framework.h"
#include "Player.h"
#include "Hud.h"

class ScreenCollision;

class GameResetEvent : public IHandler
{
    ScreenCollision* event;
public:
    GameResetEvent(ScreenCollision * e);
    ~GameResetEvent();

    void onActivated(void* data);
};
