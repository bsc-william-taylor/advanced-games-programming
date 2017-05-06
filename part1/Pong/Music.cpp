
#include "Exception.h"
#include "Music.h"

Music::Music(const char * f, unsigned int v)
{
    grab(f);
    vol(v);
}

Music::Music()
{
}

Music::~Music()
{
    if (rawData != nullptr)
    {
        Mix_FreeChunk(rawData);
        rawData = nullptr;
    }
}

Music& Music::grab(std::string filename)
{
    rawData = Mix_LoadWAV(filename.c_str());

    if (rawData == nullptr)
    {
        throw Error(AUDIO, "Couldnt load audio file", WILLIAM);
    }

    return(*this);
}

Music& Music::vol(unsigned v)
{
    if (rawData != nullptr)
    {
        Mix_VolumeChunk(rawData, v);
    }
    else
    {
        throw Error(AUDIO, "Attempted to set the volume of a sound not loaded", WILLIAM);
    }

    return(*this);
}

Music& Music::play(int times)
{
    if (rawData != nullptr)
    {
        Mix_PlayChannel(-1, rawData, times);
    }
    else
    {
        throw Error(AUDIO, "Attempted to set the volume of a sound not loaded", WILLIAM);
    }

    return(*this);
}
