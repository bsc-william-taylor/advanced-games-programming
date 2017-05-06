
#pragma once

#include "MajorInclude.h"

#define BEHAVIOUR_RESERVE_SIZE 10

class Behaviour
{
public:
    virtual void onEvent(SDL_Event&) {}
    virtual void onAccept(void *) {}
    virtual void onAction() = 0;
    virtual ~Behaviour() {}
};

class Actor
{
    std::vector<Behaviour *> behaviours;
public:
    virtual ~Actor();
    Actor();

    void pushBehaviour(Behaviour *);
    void popBehaviour(Behaviour *);
    void notifyBehaviours(SDL_Event&);
    void updateBehaviours();
};
