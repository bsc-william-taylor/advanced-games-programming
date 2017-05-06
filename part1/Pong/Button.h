
#pragma once

#include "ButtonListener.h"
#include "Texture.h"
#include "Label.h"

class Button : public IClickable
{
    ButtonListener * clickListener;
    Texture * texture;
    SDL_Rect surface;
    Label * label;
public:
    Button();
    ~Button();

    void setPosition(int x, int y, int w, int h);
    void createL(std::string, std::string, int);
    void createT(Renderer *, std::string);
    void onEvent(SDL_Event *);
    void onClick(IHandler *);

    SDL_Rect& getClickRegion();
    Texture* getTexture();
    Label* getLabel();
};
