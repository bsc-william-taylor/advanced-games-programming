
#pragma once

#include "Framework.h"

class TextureAsset
{
    SDL_Surface * textureSurface;
    std::string name;
public:
    TextureAsset(std::string name);
    ~TextureAsset();

    std::string getName();

    void grabFromFile(const char * filename);
    void* getPixels();

    SDL_Surface* getSurface();

    int getHeight();
    int getWidth();
    int getMask();
    int getBPP();
};