
#pragma once

#ifdef WIN32

#pragma comment(lib, "SDL2/SDL2_mixer.lib")
#pragma comment(lib, "SDL2/SDL2_Image.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "SDL2/SDL2_net.lib")
#pragma comment(lib, "SDL2/SDL2_TTF.lib")
#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>
#include "SDL2/SDL.h"
#include "SDL2\SDL_net.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_Image.h"
#include "TinyXml2.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

#pragma warning(disable: 4996)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

#else

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

#include "Exception.h"
#include "tinyxml2.h"


#define SAFE_RELEASE(ptr) if(ptr) { delete ptr;  ptr = NULL;} 

#define SAY_HI() SDL_ShowSimpleMessageBox(0, "Hi", "Hi", NULL)

#define NULLIFY(ptr) if(ptr == NULL) { \
		 std::cerr << "ptr is already null"; } \
		 else { ptr = NULL; }

#define SAY(value) SDL_ShowSimpleMessageBox(NULL, "SAY", to_string(value).c_str(), NULL)

#define WINDOW_X_MIDDLE 1920 / 2
#define WINDOW_X_RIGHT 1920
#define WINDOW_X_LEFT 0
#define WINDOW_Y_MIDDLE 1080 / 2
#define WINDOW_Y_BOTTOM 0
#define WINDOW_Y_TOP 1920
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

using std::to_string;
