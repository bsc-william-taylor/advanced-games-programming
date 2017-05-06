
#pragma once

#include "MajorInclude.h"

using ActorPosition = std::vector<SDL_Rect>;

class ICollidable
{
public:
    virtual ActorPosition& getPosition() = 0;
    virtual ~ICollidable() {}
};
