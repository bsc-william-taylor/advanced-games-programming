
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

#include "SDL2\SDL_main.h"
#include "SDL2\SDL_net.h"
#include "SDL2\SDL.h"

#include <Windows.h>
#include <sstream>
#include <iostream>
#include <string>

#pragma comment(lib, "SDL2/SDL2main.lib")
#pragma comment(lib, "SDL2/SDL2_net.lib")
#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "Ws2_32.lib")

enum NETWORK_ITEM_TYPE {
	CLIENT, SERVER
};

NETWORK_ITEM_TYPE selectProgramType()
{
	SDL_MessageBoxButtonData buttons[] = {
		{ 0, CLIENT, "Client" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, SERVER, "Server" }
	};

	SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL, "Server/Client",
		"Are you the server or client program",
		SDL_arraysize(buttons),
		buttons,
		NULL
	};

	int buttonID = -1;

	SDL_ShowMessageBox(&messageboxdata, &buttonID);

	if (buttonID == SERVER)
	{
		system("title Server Program");
	}
	else
	{
		system("title Client Program");
	}

	return(NETWORK_ITEM_TYPE)buttonID;
}

std::string getHostname()
{
	std::stringstream ss;
	char buffer[100];
	gethostname(buffer, 100);
	ss << buffer;
	return ss.str();
}

void prepareTutorial()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
}

void endTutorial()
{
	SDLNet_Quit();
	SDL_Quit();
}