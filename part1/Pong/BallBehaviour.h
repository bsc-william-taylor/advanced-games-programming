
#pragma once

#include "Framework.h"

class Ball;

class BallBehaviour : public Behaviour
{
    ActorPosition origin;
    Texture * spr;
    Ball * obj;

    int startDirection;
    int direction;
    int speedX;
    int speedY;
public:
    BallBehaviour(Ball *, Texture *);
    ~BallBehaviour();

    int getDirection();

    void setDirection(int i);
    void setup(int, int, int);
    void onAction();
    void negateX();
    void negateY();
    void reset();

    std::string getPositionAsString();
};
