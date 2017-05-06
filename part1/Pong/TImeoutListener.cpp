
#include "TimeoutListener.h"

TimeoutListener::TimeoutListener(IHandler * handler, int ms)
{
    this->event = handler;
    timeoutTime = ms;
    timer.start();
    active = true;
}

TimeoutListener::~TimeoutListener()
{
    if (event)
    {
        SAFE_RELEASE(event);
    }
}

void TimeoutListener::onCheck()
{
    timer.stop();

    if (active && timer.elapsed(MS) >= timeoutTime)
    {
        event->onActivated(this);
        timer.clear();
        active = false;
    }
}

void TimeoutListener::makeActive()
{
    reset();
}

void TimeoutListener::disable()
{
    active = false;
}

void TimeoutListener::reset()
{
    active = true;
    timer.start();
}
