
#include "MajorInclude.h"

class IClickable
{
public:
    virtual SDL_Rect& getClickRegion() = 0;
    virtual ~IClickable() {}
};
