
#pragma once

#include "CollisionListener.h"
#include "Framework.h"
#include "Player.h"
#include "Ball.h"

class BlockCollision : public IHandler
{
    Music clip;
public:
    BlockCollision();
    ~BlockCollision();

    int getNewAngle(int, int);
    void onActivated(void *);
};
