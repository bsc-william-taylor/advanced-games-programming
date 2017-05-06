
#pragma once

#include "Framework.h"
#include "IHandler.h"
#include "ICollidable.h"
#include "IListener.h"

struct CollisionData
{
    unsigned int indexOne, indexTwo;
    SDL_Rect area1, area2;
    ICollidable * objectOne;
    ICollidable * objectTwo;
};

class CollisionListener : public IListener
{
    ICollidable * collidable1;
    ICollidable * collodable2;
    IHandler * event;

    CollisionData * data;
public:
    CollisionListener();
    ~CollisionListener();

    void pushObjects(ICollidable *, ICollidable *, IHandler *);
    void onCheck();
};

using Collision = CollisionListener;
