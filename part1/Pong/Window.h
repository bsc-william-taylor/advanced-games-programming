
#pragma once

#include "MajorInclude.h"

class Window
{
	SDL_DisplayMode displayMode;
	SDL_Window* window;
	SDL_Rect position;
	SDL_bool shutdown;
public:
	Window();
	~Window();

	bool isOpen();

	void makeFullscreenWindow();
	void setPosition(int, int);
	void makeSimpleWindow();
	void setSize(int, int);
	void close();

	SDL_Window * getWindow();
	float getRefreshRate();
};
