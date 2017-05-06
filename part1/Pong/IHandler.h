
#pragma once

class IHandler
{
public:
    virtual void onActivated(void *) = 0;
    virtual ~IHandler() {}
};
