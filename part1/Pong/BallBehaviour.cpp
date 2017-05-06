
#include "BallBehaviour.h"
#include "Ball.h"

BallBehaviour::BallBehaviour(Ball * ptr, Texture * t)
    : startDirection(-90), obj(ptr), spr(t),
    origin(ptr->getPosition())
{
}

BallBehaviour::~BallBehaviour()
{
}

int BallBehaviour::getDirection()
{
    return direction;
}

void BallBehaviour::setDirection(int i)
{
    direction = i;
}

void BallBehaviour::reset()
{
    SDL_Rect ori = origin[0];

    spr->setPosition(ori.x, ori.y, ori.w, ori.h);
    spr->setAngle(startDirection *= -1);

    direction = spr->getAngle();
}

void BallBehaviour::setup(int d, int x, int y)
{
    direction = d;
    speedX = x;
    speedY = y;
}

void BallBehaviour::negateX()
{
    speedX *= -1;
}

void BallBehaviour::negateY()
{
    speedY *= -1;
}

std::string BallBehaviour::getPositionAsString()
{
    std::vector<SDL_Rect>& position = obj->getPosition();
    std::string strPosition = "B:";

    strPosition += to_string(position[0].x);
    strPosition += ":";
    strPosition += to_string(position[0].y);

    return strPosition;
}

void BallBehaviour::onAction()
{
    std::vector<SDL_Rect>& position = obj->getPosition();

    position[0].x += (int)(sin(direction * 3.14159265 / 180.0) * speedX);
    position[0].y += (int)(cos(direction * 3.14159265 / 180.0) * speedY);

    spr->setPosition(position[0].x, position[0].y, position[0].w, position[0].h);
}
