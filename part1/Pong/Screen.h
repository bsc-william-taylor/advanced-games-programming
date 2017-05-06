
#pragma once

#include "EventManager.h"
#include "ICollidable.h"

class Screen : public ICollidable
{
	std::vector<SDL_Rect> boxes;
public:
	Screen();
	~Screen();
	
	std::vector<SDL_Rect>& getPosition();

	enum SCREEN { LEFT, RIGHT, BOTTOM, TOP };
};
