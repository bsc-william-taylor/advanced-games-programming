
#include "Renderer.h"

Renderer::Renderer()
    : renderer(NULL)
{
}

Renderer::~Renderer()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
}

void Renderer::renderLabel(Label * str)
{
    SDL_Surface * surface = str->get();

    if (surface != NULL)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopyEx(renderer, texture,
            NULL, &str->getPosition(),
            str->getAngle(), NULL,
            SDL_FLIP_NONE
        );

        SDL_DestroyTexture(texture);
    }
}

void Renderer::clear(Window * window)
{
    SDL_RenderClear(renderer);

    int w = 0;
    int h = 0;

    SDL_GetWindowSize(window->getWindow(), &w, &h);
    SDL_RenderSetScale(renderer, (float)w / 1920, (float)h / 1080);
}

void Renderer::renderButton(Button * button)
{
    Texture* texture = button->getTexture();
    Label* string = button->getLabel();

    if (texture != NULL)
    {
        renderTexture(texture);
    }

    if (string != NULL)
    {
        renderLabel(string);
    }
}

SDL_Renderer * Renderer::get()
{
    return renderer;
}

void Renderer::renderTexture(Texture * texture)
{
    if (texture->get() != NULL)
    {
        SDL_RenderCopyEx(renderer, texture->get(),
            NULL, &texture->getPosition(),
            texture->getAngle(),
            NULL, SDL_FLIP_NONE
        );
    }
}

void Renderer::makeSimpleRenderer(Window * window)
{
    if (renderer == NULL)
    {
        renderer = SDL_CreateRenderer(window->getWindow(),
            -1, SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC
        );

        if (renderer == NULL)
        {
            throw Error(RENDERER, "Couldnt create renderer a simple renderer", WILLIAM);
        }
        else
        {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
        }
    }
    else
    {
        throw Error(RENDERER, "You cant recreate the renderer", WILLIAM);
    }
}

void Renderer::swap()
{
    SDL_RenderPresent(renderer);
}
