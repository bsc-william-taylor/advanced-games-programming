
#pragma once

#include "MajorInclude.h"
#include "Texture.h"
#include "Button.h"
#include "Label.h"
#include "Window.h"

class Renderer
{
    SDL_Renderer* renderer;
public:
    Renderer();
    ~Renderer();

    void makeSimpleRenderer(Window *);
    void renderTexture(Texture *);
    void renderButton(Button *);
    void renderLabel(Label *);
    void clear(Window *);
    void swap();

    SDL_Renderer* get();
};
