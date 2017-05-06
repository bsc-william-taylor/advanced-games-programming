
#pragma once

#include "Framework.h"

class Ball;

class AiBehaviour : public Behaviour
{
    ActorPosition origin;
    Texture * spr;
    Ball * ball;
public:
    AiBehaviour(Ball *);
    ~AiBehaviour();

    void onAccept(void *);
    void onAction();
    void reset();
};
