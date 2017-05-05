
#include "HighPrecisionTimer.h"

HighPrecisionTimer::HighPrecisionTimer()
{
    tickFreq = SDL_GetPerformanceFrequency();
    start();
    stop();
}

HighPrecisionTimer::~HighPrecisionTimer()
{
}

void HighPrecisionTimer::start()
{
    startTicks = SDL_GetPerformanceCounter();
}

void HighPrecisionTimer::stop()
{
    stopTicks = SDL_GetPerformanceCounter();
}

float HighPrecisionTimer::elapsed(TimeType type)
{
    stopTicks = SDL_GetPerformanceCounter();
    return(difference(type));
}

void HighPrecisionTimer::clear()
{
    start();
    stop();
}

float HighPrecisionTimer::difference(TimeType type)
{
    float difference = 0.0f;

    switch (type)
    {
        case TimeType::Seconds:
        {
            difference = (float)(stopTicks - startTicks);
            break;
        }

        case TimeType::Milliseconds:
        {
            difference = (float)(1.0e3*(stopTicks - startTicks));
            break;
        }

        case TimeType::Nanoseconds:
        {
            difference = (float)(1.0e9*(stopTicks - startTicks));
            break;
        }
    };

    return(difference / tickFreq);
}

unsigned int HighPrecisionTimer::current()
{
    currentTicks = SDL_GetPerformanceCounter();
    return(currentTicks);
}