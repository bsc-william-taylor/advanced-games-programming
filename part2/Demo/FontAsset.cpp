
#include "FontAsset.h"

FontAsset::FontAsset(std::string name)
{
    colour = { 255, 255, 255 };
    this->name = name;
    text = name;
    font = NULL;
}

FontAsset::~FontAsset()
{
    if (font != NULL) 
    {
        TTF_CloseFont(font);
    }
}

SDL_Surface * FontAsset::generateTexture()
{
    SDL_Surface * fontSurface = NULL;

    if (font == NULL || sz != -1)
    {
        font = TTF_OpenFont(filename.c_str(), sz);
        sz = -1;
    }

    if (font)
    {
        fontSurface = TTF_RenderText_Blended(font, text.c_str(), colour);
        TTF_CloseFont(font);
        font = NULL;
    }

    return fontSurface;
}

void FontAsset::setColour(SDL_Color c)
{
    colour = c;
}

void FontAsset::setText(const char * t)
{
    text = t;
}

void FontAsset::grabFromFile(std::string font)
{
    filename = font;
}

void FontAsset::openAtSize(int sz)
{
    this->sz = sz;
}

std::string FontAsset::getName()
{
    return name;
}