
#pragma once

#include "Framework.h"

class FontAsset
{
    SDL_Color colour;
    TTF_Font* font;
    unsigned int sz;

    std::string filename;
    std::string text;
    std::string name;
public:
    FontAsset(std::string name);
    ~FontAsset();

    SDL_Surface * generateTexture();

    void grabFromFile(std::string);
    void setColour(SDL_Color c);
    void setText(const char *);
    void openAtSize(int);

    std::string getName();
};