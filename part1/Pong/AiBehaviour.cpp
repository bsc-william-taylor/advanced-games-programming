
#include "AiBehaviour.h"
#include "Player.h"
#include "Ball.h"

AiBehaviour::AiBehaviour(Ball * ball)
    : ball(ball)
{
}

AiBehaviour::~AiBehaviour()
{
}

void AiBehaviour::onAction()
{
    SDL_Rect ballPosition = ball->getPosition()[0];
    SDL_Rect sprPosition = spr->getPosition();

    int distancey = 0;

    if (ballPosition.y > sprPosition.y + 8)
        distancey = 8;
    if (ballPosition.y < sprPosition.y - 8)
        distancey = -8;

    SDL_Rect& position = spr->getPosition();
    if (position.y + position.h + distancey <= 1060 && position.y + distancey >= 20)
    {
        spr->getPosition().y += distancey;
    }
}

void AiBehaviour::onAccept(void * obj)
{
    spr = static_cast<Player *>(obj)->getTexture();
}

void AiBehaviour::reset()
{
}
