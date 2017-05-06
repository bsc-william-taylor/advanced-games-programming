
#pragma once

#include "TimeoutListener.h"
#include "MajorInclude.h"
#include "Renderer.h"
#include "XMLFile.h"
#include "Music.h"
#include "Bank.h"
#include "Actor.h"
#include "Game.h"

#include <algorithm>
#include <iostream>
#include <string>

#define global_string const static std::string
#define global_float const static float
#define global_int const static int

#define CENTER_X SDL_WINDOWPOS_CENTERED
#define CENTER_Y SDL_WINDOWPOS_CENTERED

extern void onGameStart(Game& game, Bank*, SceneManager*);