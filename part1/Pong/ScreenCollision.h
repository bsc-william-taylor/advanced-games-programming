
#pragma once

#include "CollisionListener.h"
#include "Framework.h"
#include "TimeoutListener.h"
#include "Player.h"
#include "Ball.h"

class ScreenCollision : public IHandler
{
    TimeoutListener timeoutListener;
    StatisticsFile * stats;
    SceneManager * mgr;
    Ball* ball;
    bool triggered;
    Music clip;
public:
    ScreenCollision(SceneManager * mgr, StatisticsFile * f);
    ~ScreenCollision();

    void onActivated(void *);
    void restart();
};
