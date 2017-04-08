/**
 * 
 * Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
 *  
 * This software is provided 'as-is', without any 
 * express or implied warranty. In no event will 
 * the authors be held liable for any damages 
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute 
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; 
 *    you must not claim that you wrote the original software. 
 *    If you use this software in a product, an acknowledgment 
 *    in the product documentation would be appreciated but 
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, 
 *    and must not be misrepresented as being the original software.
 *  
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include "CommonHeader.h"

// a class which sets up the window for the game
class Window
{
private:
	// info on the computers display
	SDL_DisplayMode displayMode;
	// a pointer to the actual window class
	SDL_Window * window;
	// the position and size of the window
	SDL_Rect position;
	// should the window close
	SDL_bool shutdown;
public:
	// Constructor & Deconstructor
	Window();
	~Window();

	// a check function to tell if the window is open 
	bool isOpen();

	// makes the window fullscreen
	void makeFullscreenWindow();
	// sets the position of the window
	void setPosition(int, int);
	// makes a simple window at the specified position
	void makeSimpleWindow();
	// sets the size of the window
	void setSize(int, int);
	// closes the window
	void close();
public:
	// returns a pointer to the SDL_Window struct
	SDL_Window * getWindow();
	// returns the refresh rate of the monitor
	float getRefreshRate();
};
