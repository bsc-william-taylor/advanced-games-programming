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
 */

#ifndef __FRAMEWORK__H__
#define __FRAMEWORK__H__

// include these common framework headers
#include "TimeoutListener.h"
#include "CommonHeader.h"
#include "Renderer.h"
#include "XMLFile.h"
#include "Music.h"
#include "Bank.h"
#include "Actor.h"
#include "Game.h"

// also add these standard headers for the user
#include <algorithm>
#include <iostream>
#include <string>

// couple of macros for when we use globals (not recommended)
#define global_string const static std::string
#define global_float const static float
#define global_int const static int

// anoter macro to make centering a window more readable
#define CENTER_X SDL_WINDOWPOS_CENTERED
#define CENTER_Y SDL_WINDOWPOS_CENTERED

// onGameStartFunction which is defined by the user
extern void onGameStart(Game& game, Bank*, SceneManager*);

#endif