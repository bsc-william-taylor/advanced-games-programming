
#pragma once

#include "EventManager.h"
#include "ICollidable.h"

enum class ScreenSide 
{ 
    LEFT, 
    RIGHT, 
    BOTTOM, 
    TOP 
};

class Screen : public ICollidable
{
	std::vector<SDL_Rect> boxes;
public:
	Screen();
	~Screen();
	
	std::vector<SDL_Rect>& getPosition();
};
