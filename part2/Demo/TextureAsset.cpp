
#include "TextureAsset.h"

TextureAsset::TextureAsset(std::string n)
{
    textureSurface = nullptr;
    name = n;
}

TextureAsset::~TextureAsset()
{
    if (textureSurface != nullptr) 
    {
        SDL_FreeSurface(textureSurface);
    }
}

void TextureAsset::grabFromFile(const char * filename)
{
    textureSurface = IMG_Load(filename);

    if (textureSurface == nullptr)
    {
        throw Error(ErrorType::FileIO, std::string(filename, " couldnt load a texture"));
    }
}

std::string TextureAsset::getName()
{
    return name;
}

SDL_Surface * TextureAsset::getSurface()
{
    return textureSurface;
}

void * TextureAsset::getPixels()
{
    return textureSurface->pixels;
}

int TextureAsset::getBPP()
{
    return this->textureSurface->format->BytesPerPixel;
}

int TextureAsset::getMask()
{
    return this->textureSurface->format->Rmask;
}

int TextureAsset::getWidth()
{
    return textureSurface->w;
}

int TextureAsset::getHeight()
{
    return textureSurface->h;
}