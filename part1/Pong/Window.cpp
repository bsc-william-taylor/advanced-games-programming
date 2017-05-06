
#include "Window.h"

Window::Window()
    : window(NULL)
{
    SDL_GetCurrentDisplayMode(NULL, &displayMode);
    shutdown = SDL_FALSE;
}

Window::~Window()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        NULLIFY(window);
    }
}

float Window::getRefreshRate()
{
    if (displayMode.refresh_rate == NULL)
    {
        return 60.0F;
    }
    else
    {
        return displayMode.refresh_rate;
    }
}

bool Window::isOpen()
{
    return(window != NULL && shutdown == SDL_FALSE);
}

void Window::close()
{
    shutdown = SDL_TRUE;
}

void Window::makeFullscreenWindow()
{
    if (displayMode.w >= 1920 || displayMode.h >= 1080) {
        displayMode.w = 1920;
        displayMode.h = 1080;
    }

    window = SDL_CreateWindow("",
        NULL, NULL, displayMode.w, displayMode.h,
        SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (window == NULL)
    {
        throw Error(WINDOW, "Couldnt create window");
    }
}

void Window::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Window::setSize(int w, int h)
{
    position.w = w;
    position.h = h;
}

SDL_Window * Window::getWindow()
{
    return window;
}

void Window::makeSimpleWindow()
{
    window = SDL_CreateWindow("",
        position.x, position.y,
        position.w, position.h,
        SDL_WINDOW_ALLOW_HIGHDPI |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        throw Error(WINDOW, "Couldnt create window");
    }
}
