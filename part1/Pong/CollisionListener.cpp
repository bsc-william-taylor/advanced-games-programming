
#include "CollisionListener.h"

CollisionListener::CollisionListener()
{
    data = new CollisionData();
    event = NULL;
}

CollisionListener::~CollisionListener()
{
    SAFE_RELEASE(data);
}

void CollisionListener::pushObjects(ICollidable * c1, ICollidable * c2, IHandler * e)
{
    collidable1 = c1;
    collodable2 = c2;
    event = e;
}

void CollisionListener::onCheck()
{
    if (event != NULL)
    {
        std::vector<SDL_Rect>& obj1 = collidable1->getPosition();
        std::vector<SDL_Rect>& obj2 = collodable2->getPosition();

        bool activated = false;

        for (unsigned i = 0; i < obj1.size(); i++)
        {
            bool breakLoop = false;
            SDL_Rect rect = obj1[i];

            for (unsigned z = 0; z < obj2.size(); z++)
            {
                SDL_Rect size = obj2[z];

                if (rect.x <= size.x + size.w && rect.x + rect.w >= size.x)
                {
                    if (rect.y <= size.y + size.h && rect.y + rect.h >= size.y)
                    {
                        breakLoop = true;

                        data->indexOne = i;
                        data->indexTwo = z;
                        data->area1 = rect;
                        data->area2 = size;
                        break;
                    }
                }
            }

            if (breakLoop)
            {
                activated = true;
                break;
            }
        }

        if (activated)
        {
            data->objectOne = collidable1;
            data->objectTwo = collodable2;
            event->onActivated(data);
        }
    }
}
