
#pragma once

#include "MajorInclude.h"

class Music
{
	Mix_Chunk* rawData;
public:
	Music(const char * filename, unsigned int volume);
	Music();
	~Music();

	Music& grab(std::string filename);
	Music& vol(unsigned volume);
	Music& play(int times = 0);
};
