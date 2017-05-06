
#pragma once

#include "MajorInclude.h"

class Renderer;

class Texture
{
    struct TextureEntry
    {
        SDL_Surface* surface;
        SDL_Texture* texture;
        std::string filename;
    };

    SDL_Texture * texture;
    SDL_Rect position;
    double angle;
public:
    Texture();
    ~Texture();

    void create(Renderer * renderer, std::string filename);
    void setPosition(int x, int y, int w, int h);
    void setAngle(double newAngle);
public:
    SDL_Rect& getPosition();
    SDL_Texture * get();
    double getAngle();
private:
    SDL_Texture * checkForDuplicate(Renderer * renderer, std::string str);
    static std::vector<TextureEntry *> loaded_textures;
    static unsigned int reference_count;
};
