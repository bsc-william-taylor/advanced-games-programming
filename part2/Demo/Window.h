
#pragma once

#include "Framework.h"

class Window
{
    SDL_GLContext windowContext;
    SDL_Window * window;
    SDL_Rect dimensions;

    const char * title;
    bool fullscreen;
public:
    Window();
    ~Window();

    void setPosition(int x, int y);
    void setTitle(const char * t);
    void setSize(int w, int h);
    void makeFullscreen();
    void swapBuffers();
    void create();

    int getHeight();
    int getWidth();

    SDL_Window* getWindow();
};