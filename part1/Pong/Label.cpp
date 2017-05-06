
#include "Label.h"

std::vector<FontEntry *> Label::fonts;
unsigned int Label::reference_count = 0;

Label::Label()
    : surface(NULL),
    text(" ")
{
    colour = { 255, 255, 255 };
    reference_count++;
}

Label::~Label()
{
    reference_count--;

    if (reference_count == NULL)
    {
        for (auto&& font : fonts)
        {
            if (font->font)
            {
                TTF_CloseFont(font->font);
                NULLIFY(font->font);
            }
        }
    }
}

void Label::setPosition(int x, int y, Alignment e)
{
    position = { x, y, surface->w, surface->h };
    switch (e)
    {
    case CENTER:
    {
        position.x -= surface->w / 2;
        position.y -= surface->h / 2;
        break;
    }

    case LEFT:
    {
        position.x -= surface->w / 2;
        break;
    }

    default:
        break;
    }
}

const char * Label::getText()
{
    return text;
}

double Label::getAngle()
{
    return 0.0F;
}

SDL_Rect& Label::getPosition()
{
    return position;
}

SDL_Surface * Label::get()
{
    return surface;
}

void Label::setColour(SDL_Color colour)
{
    this->colour = colour;
}

void Label::create(std::string fontFile, std::string text, int sz)
{
    this->text = text.c_str();

    if (surface)
    {
        SDL_FreeSurface(surface);
    }

    TTF_Font* font = checkForDuplicates(fontFile, sz);

    if (font == NULL)
    {
        auto returnFont = new FontEntry();
        returnFont->font = TTF_OpenFont(fontFile.c_str(), sz);
        returnFont->filename = fontFile;
        returnFont->sz = sz;

        fonts.push_back(returnFont);
        font = (returnFont->font);
    }

    surface = TTF_RenderText_Blended(font, text.c_str(), colour);

    position.x = NULL;
    position.y = NULL;
    position.w = surface->w;
    position.h = surface->h;
}

TTF_Font* Label::checkForDuplicates(std::string str, unsigned int fsz)
{
    for (unsigned int i = 0; i < fonts.size(); i++)
    {
        if (fonts[i]->filename == str && fonts[i]->sz == fsz)
        {
            return fonts[i]->font;
        }
    }

    return nullptr;
}