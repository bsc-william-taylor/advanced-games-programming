
#include "Window.h"

Window::Window()
	: fullscreen(false),
	  window(NULL),
	  title("")
{
}

Window::~Window()
{
	if (window != NULL) 
	{
		SDL_GL_DeleteContext(windowContext);
		SDL_DestroyWindow(window);
	}
}

int Window::getHeight()
{
	return dimensions.h;
}

int Window::getWidth()
{
	return dimensions.w;
}

void Window::setPosition(int x, int y)
{
	dimensions.x = x;
	dimensions.y = y;
}

void Window::setTitle(const char * t)
{
	title = t;
}

void Window::setSize(int w, int h)
{
	dimensions.w = w;
	dimensions.h = h;
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Window::create()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (!fullscreen) 
	{
		window = SDL_CreateWindow(title,
			dimensions.x, dimensions.y,
			dimensions.w, dimensions.h,
			SDL_WINDOW_OPENGL
		);
	} 
	else 
	{
		window = SDL_CreateWindow(title,
			dimensions.x, dimensions.y,
			dimensions.w, dimensions.h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		);
	}

	windowContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, windowContext);
}

void Window::makeFullscreen() 
{
	SDL_DisplayMode current;
	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

		if (should_be_zero == 0) {
			dimensions.h = current.h;
			dimensions.w = current.w;
			dimensions.x = 0;
			dimensions.y = 0;
			break;
		}
	}

	fullscreen = true;
}

SDL_Window * Window::getWindow()
{
	return window;
}