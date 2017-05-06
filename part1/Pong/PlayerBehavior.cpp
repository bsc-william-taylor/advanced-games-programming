
#include "PlayerBehavior.h"
#include "Player.h"

PlayerBehaviour::PlayerBehaviour(int s, bool r)
    : right(r), speed(s)
{
    reset();
}

PlayerBehaviour::~PlayerBehaviour()
{
}

void PlayerBehaviour::onAction()
{
    if (keys[0] && right)
        move(spr, speed);
    if (keys[1] && right)
        move(spr, -speed);
    if (keys[2] && !right)
        move(spr, -speed);
    if (keys[3] && !right)
        move(spr, speed);
}

void PlayerBehaviour::onEvent(SDL_Event& e)
{
    if (e.key.state == SDL_PRESSED)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_DOWN: keys[0] = true; break;
            case SDLK_UP: keys[1] = true; break;
            case SDLK_w: keys[2] = true; break;
            case SDLK_s: keys[3] = true; break;

        default:
            break;
        }
    }

    if (e.key.state == SDL_RELEASED)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_DOWN: keys[0] = false; break;
            case SDLK_UP: keys[1] = false; break;
            case SDLK_w: keys[2] = false; break;
            case SDLK_s: keys[3] = false; break;

        default:
            break;
        }
    }
}

void PlayerBehaviour::onAccept(void * obj)
{
    spr = static_cast<Player *>(obj)->getTexture();
}

void PlayerBehaviour::reset()
{
    for (int i = 0; i < 4; i++)
    {
        keys[i] = false;
    }
}

void PlayerBehaviour::move(Texture * texture, int speed)
{
    SDL_Rect& position = texture->getPosition();

    if (position.y + position.h + speed <= 1060 && position.y + speed >= 20)
    {
        texture->getPosition().y += speed;
    }
}
