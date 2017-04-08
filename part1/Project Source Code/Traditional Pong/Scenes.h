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

/*
	This is just an include file that includes all the scenes
																*/
#ifndef __SCENES_H__
#define __SCENES_H__

// include all the scenes
#include "OnlinePlayerMap.h"
#include "TwoPlayerMap.h"
#include "OnePlayerMap.h"
#include "Multiplayer.h"
#include "Statistics.h"
#include "Gameover.h"
#include "Controls.h"
#include "About.h"
#include "Menu.h"

// a simple macro to change the version text depending on the platform
#ifdef WIN32
    #define VERSION_STRING "Version 1.0W"
#else
    #define VERSION_STRING "Version 1.0L"
#endif

// give each scene an ID
enum SceneIDs {
	ONLINE_PLAYER_MAP, ONE_PLAYER, TWO_PLAYER,
	MULTIPLAYER, STATS, CONTROLS, GAMEOVER,
	ABOUT, MENU
};

#endif
