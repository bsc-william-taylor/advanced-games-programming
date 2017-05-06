
#pragma once

class IListener
{
public:
    virtual void onCheck() = 0;
    virtual ~IListener() {}
};

