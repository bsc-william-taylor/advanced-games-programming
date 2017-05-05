
#pragma once

#include "Framework.h"

enum class TimeType
{
    Seconds, Milliseconds, Nanoseconds
};

class HighPrecisionTimer
{
    unsigned int currentTicks;
    unsigned int startTicks;
    unsigned int stopTicks;
    unsigned int tickFreq;
public:
    HighPrecisionTimer();
    ~HighPrecisionTimer();

    float difference(TimeType);
    float elapsed(TimeType);

    void start();
    void stop();
    void clear();

    unsigned int current();
};