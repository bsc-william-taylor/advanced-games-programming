
#include "Actor.h"

Actor::Actor()
{
    behaviours.reserve(BEHAVIOUR_RESERVE_SIZE);
}

Actor::~Actor()
{
}

void Actor::pushBehaviour(Behaviour * ptr)
{
    if (ptr != NULL)
    {
        behaviours.push_back(ptr);
    }
    else
    {
        throw Error(GAME, "Entering null behaviour", WILLIAM);
    }
}

void Actor::notifyBehaviours(SDL_Event& e)
{
    for (auto&& behaviour : behaviours)
    {
        behaviour->onEvent(e);
    }
}

void Actor::popBehaviour(Behaviour * ptr)
{
    behaviours.pop_back();
}

void Actor::updateBehaviours()
{
    for (auto&& behaviour : behaviours)
    {
        behaviour->onAction();
    }
}
