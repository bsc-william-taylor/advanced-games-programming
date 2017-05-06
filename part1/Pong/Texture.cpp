
#include "Renderer.h"
#include "Texture.h"

std::vector<Texture::TextureEntry *> Texture::loaded_textures;
unsigned int Texture::reference_count = 0;

Texture::Texture()
    : angle(0)
{
    ++reference_count;
}

Texture::~Texture()
{
    --reference_count;

    if (reference_count == 0)
    {
        for (auto&& tex : loaded_textures)
        {
            if (tex->surface != NULL)
            {
                SDL_FreeSurface(tex->surface);
                NULLIFY(tex->surface);
            }

            if (tex->texture != NULL)
            {
                SDL_DestroyTexture(tex->texture);
                NULLIFY(tex->texture);
            }
        }

        loaded_textures.clear();
    }
}

SDL_Texture * Texture::checkForDuplicate(Renderer * renderer, std::string str)
{
    for (unsigned i = 0; i < loaded_textures.size(); i++)
    {
        if (loaded_textures[i]->filename == str)
        {
            return loaded_textures[i]->texture;
        }
    }

    return NULL;
}

void Texture::create(Renderer * renderer, std::string filename)
{
    texture = checkForDuplicate(renderer, filename);

    if (texture == NULL)
    {
        TextureEntry * entry = new TextureEntry();
        entry->surface = IMG_Load(filename.c_str());
        entry->filename = filename;

        if (entry->surface == NULL)
        {
            throw Error(TEXTURE, "Couldnt create texture : " + filename, WILLIAM);
        }
        else
        {
            entry->texture = SDL_CreateTextureFromSurface(
                renderer->get(),
                entry->surface
            );

            SDL_FreeSurface(entry->surface);
            entry->surface = NULL;
            loaded_textures.push_back(entry);
            texture = entry->texture;
        }
    }
}

void Texture::setPosition(int x, int y, int w, int h)
{
    position.x = x;
    position.y = y;
    position.w = w;
    position.h = h;
}

void Texture::setAngle(double a)
{
    angle = a;
}

double Texture::getAngle()
{
    return angle;
}

SDL_Rect& Texture::getPosition()
{
    return position;
}

SDL_Texture * Texture::get()
{
    return texture;
}
