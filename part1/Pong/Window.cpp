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

#include "Window.h"

// Constructor & Deconstructor
Window::Window()
	: window(NULL)
{
	// Get the current display mode and store it in the displayMode struct
	SDL_GetCurrentDisplayMode(NULL, &displayMode);
	// and just set the shutdown command to false
	shutdown = SDL_FALSE;
}

Window::~Window()
{
	// if a window has been created
	if(window)
	{
		// destroy the window
		SDL_DestroyWindow(window);
		NULLIFY(window);
	}
}

// returns the refresh rate of the monitor
float Window::getRefreshRate()
{
	// if the refresh rate isnt specified
	if (displayMode.refresh_rate == NULL) 
	{
		// assume 60hz
		return 60.0F;
	}
	else 
	{
		// else return the rate specified
		return displayMode.refresh_rate;
	}
}

// a check function to tell if the window is open
bool Window::isOpen()
{
	return(window != NULL && shutdown == SDL_FALSE);
}

// tells the window to close
void Window::close()
{
	shutdown = SDL_TRUE;
}

void Window::makeFullscreenWindow()
{
	// dont display across two monitors only one
    if(displayMode.w >= 1920 || displayMode.h >= 1080) {
        displayMode.w = 1920;
        displayMode.h = 1080;
    }

	// create the window
	window = SDL_CreateWindow("",
		NULL, NULL, displayMode.w, displayMode.h,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI
	);

	// if it fails throw an exception
	if(window == NULL)
	{
		throw Error(WINDOW, "Couldnt create window");
	}
}

// set the position of the window
void Window::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

// set the size of the window
void Window::setSize(int w, int h)
{
	position.w = w;
	position.h = h;
}

// returns a pointer to the SDL_Window variable
SDL_Window * Window::getWindow()
{
	return window;
}

// makes a simple window at the specified position
void Window::makeSimpleWindow()
{
	// create the window
	window = SDL_CreateWindow("",
		position.x,	position.y,
		position.w,	position.h,
		SDL_WINDOW_ALLOW_HIGHDPI |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_SHOWN
	);

	// on fail throw an exception
	if(window == NULL)
	{
		throw Error(WINDOW, "Couldnt create window");
	}
}
