
#include "ExternalLibraries.h"

ExternalLibraries::ExternalLibraries()
    : IMG_Params(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_JPG),
    MIX_Params(MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3),
    SDL_Params(SDL_INIT_EVERYTHING)
{
}

ExternalLibraries::~ExternalLibraries()
{
}

void ExternalLibraries::importLibraries()
{
    if (SDL_Init(SDL_Params) != NULL)
    {
        throw Error(GAME, "Couldnt init SDL");
    }

    if (IMG_Init(IMG_Params) != IMG_Params)
    {
        throw Error(GAME, "Couldnt init IMG");
    }

    if (TTF_Init() != NULL)
    {
        throw Error(GAME, "Couldnt init TTF");
    }

    if (Mix_Init(MIX_Params) == NULL)
    {
        throw Error(GAME, "Couldnt init Mixer");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2014) < NULL)
    {
        throw Error(GAME, "Error with grabbing audio device");
    }

    if (SDLNet_Init())
    {
        throw Error(GAME, "Error with grabbing network device");
    }
}

void ExternalLibraries::freeLibraries()
{
    Mix_CloseAudio();
    SDLNet_Quit();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
