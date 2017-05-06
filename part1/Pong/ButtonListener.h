
#include "MajorInclude.h"
#include "IListener.h"
#include "IClickable.h"
#include "IHandler.h"

class ButtonListener : public IListener
{
    IClickable * object;
    IHandler * event;
public:
    ButtonListener();
    ~ButtonListener();

    void pushObjects(IClickable *, IHandler *);
    void onEvent(SDL_Event *);
    void onCheck();
};
