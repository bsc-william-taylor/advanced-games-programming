
#pragma once

#include "MajorInclude.h"

class ExternalLibraries
{
	unsigned int IMG_Params;
	unsigned int MIX_Params;
	unsigned int SDL_Params;
public:
	ExternalLibraries();
	~ExternalLibraries();

	void importLibraries();
	void freeLibraries();
};
