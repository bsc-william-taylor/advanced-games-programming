
#pragma once

#include "Framework.h"
#include "IHandler.h"
#include "highPrecisionTimer.h"
#include "ICollidable.h"
#include "IListener.h"

class TimeoutListener : public IListener
{
    HighPrecisionTimer timer;
    unsigned int timeoutTime;
    IHandler * event;
    bool active;
public:
    TimeoutListener(IHandler * handler, int ms);
    TimeoutListener() = default;
    ~TimeoutListener();

    void makeActive();
    void disable();
    void onCheck();
    void reset();
};
