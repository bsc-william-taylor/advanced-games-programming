/**
 *
 * Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
 *
 * This software is provided 'as-is', without any
 * express or implied warranty. In no event will
 * the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#pragma once

// if we are on windows
#ifdef WIN32

// link all the libraries tha we will use
#pragma comment(lib, "SDL2/SDL2_mixer.lib")
#pragma comment(lib, "SDL2/SDL2_Image.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "SDL2/SDL2_net.lib")
#pragma comment(lib, "SDL2/SDL2_TTF.lib")
#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "Ws2_32.lib")

// an include all these header files
#include <Windows.h>
#include "SDL2/SDL.h"
#include "SDL2\SDL_net.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_Image.h"
#include "TinyXml2.h"

// include these standard files
#include <functional>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

// disable these warnings that do nothing by annoy me
#pragma warning(disable: 4996)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

// if we are on another platform (LINUX)
#else

// include these headers if we are on linux
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_net.h"
#include "tinyxml2.h"

// and these standard headers
#include <functional>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

#endif

#ifndef NULL
	#define NULL 0
#endif

// simple memory macro helps stop deleting memory already deallocated
#define SAFE_RELEASE(ptr) if(ptr) { delete ptr;  ptr = NULL;} 

// simple HI macro to test if some code is reached
#define SAY_HI() SDL_ShowSimpleMessageBox(0, "Hi", "Hi", NULL)

// makes a pointer null
#define NULLIFY(ptr) if(ptr == NULL) { \
		 std::cerr << "ptr is already null"; } \
		 else { ptr = NULL; }

#define SAY(value) SDL_ShowSimpleMessageBox(NULL, "SAY", to_string(value).c_str(), NULL)

// some simple macros reguarding screen dimensions
#define WINDOW_X_MIDDLE 1920 / 2
#define WINDOW_X_RIGHT 1920
#define WINDOW_X_LEFT 0
#define WINDOW_Y_MIDDLE 1080 / 2
#define WINDOW_Y_BOTTOM 0
#define WINDOW_Y_TOP 1920
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// make to_string global
using std::to_string;

// include these headers for any platform
#include "Exception.h"
#include "tinyxml2.h"
