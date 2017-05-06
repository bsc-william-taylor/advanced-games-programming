
#include "Button.h"

Button::Button()
    : clickListener(new ButtonListener()),
    texture(NULL),
    label(NULL)
{
}

Button::~Button()
{
    SAFE_RELEASE(clickListener);
    SAFE_RELEASE(texture);
    SAFE_RELEASE(label);
}

void Button::onClick(IHandler * e)
{
    clickListener->pushObjects(this, e);
}

SDL_Rect& Button::getClickRegion()
{
    return surface;
}

void Button::onEvent(SDL_Event * event)
{
    clickListener->onEvent(event);
    clickListener->onCheck();
}

void Button::setPosition(int x, int y, int w, int h)
{
    surface = { x, y, w, h };

    int mdx = x + (w / 2);
    int mdy = y + (h / 2);

    if (label)
    {
        label->setPosition(mdx, mdy, CENTER);
    }

    if (texture)
    {
        texture->setPosition(x, y, w, h);
    }
}

void Button::createL(std::string str, std::string str2, int sz)
{
    if (label) SAFE_RELEASE(label);

    label = new Label();
    label->create(str, str2, sz);
}

Texture * Button::getTexture()
{
    return texture;
}

Label * Button::getLabel()
{
    return label;
}

void Button::createT(Renderer * renderer, std::string filename)
{
    if (texture) SAFE_RELEASE(texture);

    texture = new Texture();
    texture->create(renderer, filename);
}
