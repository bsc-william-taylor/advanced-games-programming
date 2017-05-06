
#pragma once

#include "MajorInclude.h"

enum TimeType {
    SECONDS, MS, NS
};

class HighPrecisionTimer
{
    unsigned int currentTicks;
    unsigned int startTicks;
    unsigned int stopTicks;
    unsigned int freq;
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
