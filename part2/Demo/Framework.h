
#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <algorithm>
#include <string>
#include <memory>
#include <time.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <map>

#include "SDL2/SDL.h"
#include "glew/glew.h"
#include "gl/gl.h"
#include "assimp/postprocess.h"    
#include "assimp/Importer.hpp"          
#include "assimp/scene.h"   
#include "Freeimage/FreeImage.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Exception.h"

#pragma warning(disable : 4305)
#pragma warning(disable : 4018)
#pragma warning(disable : 4244)

#pragma comment(lib, "Freeimage/FreeImage.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "SDL2/SDL2_ttf.lib")
#pragma comment(lib, "SDL2/SDL2_image.lib")
#pragma comment(lib, "assimp/assimp.lib") 
#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew/glew32.lib")

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(ptr) if(ptr) { delete ptr; ptr = 0; }
#else
	#error("SAFE_RELEASE macro already supplied")
#endif

#ifndef PI
	#define PI 3.14159265359F
#else
	#error("PI macro already supplied")
#endif