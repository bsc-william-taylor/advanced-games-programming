
#pragma once

#include "Framework.h"

class Player;

class PlayerBehaviour : public Behaviour
{
    ActorPosition origin;
    Texture* spr;
    bool keys[4];
    bool right;
    int speed;
public:
    PlayerBehaviour(int, bool);
    ~PlayerBehaviour();

    void onEvent(SDL_Event&);
    void onAccept(void *);
    void onAction();
    void reset();
    void move(Texture *, int);
};
