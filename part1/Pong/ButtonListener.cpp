
#include "ButtonListener.h"

ButtonListener::ButtonListener()
    : event(NULL)
{
}

ButtonListener::~ButtonListener()
{
}

void ButtonListener::pushObjects(IClickable * c, IHandler * e)
{
    object = c;
    event = e;
}

void ButtonListener::onEvent(SDL_Event * eventData)
{
    if (eventData->button.state == SDL_PRESSED && eventData->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Rect& pos = object->getClickRegion();

        int mx = eventData->motion.x;
        int my = eventData->motion.y;

        if (mx >= pos.x && mx <= pos.x + pos.w && my >= pos.y && my <= pos.y + pos.h)
        {
            event->onActivated(object);
        }
    }
}

void ButtonListener::onCheck()
{
}
