
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

enum class ProgramType
{
    Client, Server
};

ProgramType selectProgramType()
{
    SDL_MessageBoxButtonData buttons[] = {
        { 0, (int)ProgramType::Client, "Client" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, (int)ProgramType::Server, "Server" }
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

    if (buttonID == (int)ProgramType::Server)
    {
        system("title Server Program");
    }
    else
    {
        system("title Client Program");
    }

    return(ProgramType)buttonID;
}

std::string getHostname()
{
    std::stringstream ss;
    char buffer[100];
    gethostname(buffer, 100);
    ss << buffer;
    return ss.str();
}