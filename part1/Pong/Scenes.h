
#pragma once

#include "OnlinePlayerMap.h"
#include "TwoPlayerMap.h"
#include "OnePlayerMap.h"
#include "Multiplayer.h"
#include "Statistics.h"
#include "Gameover.h"
#include "Controls.h"
#include "About.h"
#include "Menu.h"

#ifdef WIN32
    #define VERSION_STRING "Version 1.0W"
#else
    #define VERSION_STRING "Version 1.0L"
#endif

enum SceneIDs {
    ONLINE_PLAYER_MAP,
    ONE_PLAYER,
    TWO_PLAYER,
    MULTIPLAYER,
    STATS,
    CONTROLS,
    GAMEOVER,
    ABOUT,
    MENU
};
