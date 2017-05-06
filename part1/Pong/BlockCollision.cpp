
#include "BlockCollision.h"
#include "Hud.h"

BlockCollision::BlockCollision()
{
    clip.grab("data/block.wav");
    clip.vol(50);
}

BlockCollision::~BlockCollision()
{
}

int BlockCollision::getNewAngle(int distance, int angle)
{
    int newAngle = 0;

    if (distance != 0)
    {
        newAngle = (asin((float)distance / 125)) * 180.0 / 3.14159265;
    }

    return(angle + newAngle);
}

void BlockCollision::onActivated(void * data)
{
    CollisionData * info = static_cast<CollisionData *>(data);
    Ball * ball = static_cast<Ball *>(info->objectOne);
    BallBehaviour * bv = ball->getBehaviour();

    SDL_Rect pos2 = info->area2;
    SDL_Rect pos1 = info->area1;

    int dfc = (pos2.y + (pos2.h / 2)) - (pos1.y + (pos1.h / 2));

    if (pos2.x == 50)
    {
        bv->setup(getNewAngle(dfc, 90), 20, 20);
    }
    else if (pos2.x == 1870)
    {
        bv->setup(getNewAngle(dfc, 270), 20, -20);
    }

    clip.play(0);
}
