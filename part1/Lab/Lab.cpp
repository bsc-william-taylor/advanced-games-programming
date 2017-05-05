
#include "Lab.h"

int main(int argc, char * argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    ProgramType programType = selectProgramType();
    IPaddress ipAddress;
    UDPpacket* packet;
    UDPsocket socket;

    char buffer[512];
    int quit = 0;

    if (programType == ProgramType::Server)
    {
        socket = SDLNet_UDP_Open(2000);
        packet = SDLNet_AllocPacket(512);

        while (!quit)
        {
            if (SDLNet_UDP_Recv(socket, packet))
            {
                if (strcmp((char*)packet->data, "quit") == 0)
                {
                    quit = true;
                }
                else
                {
                    system("cls");
                    strcpy(buffer, (char*)packet->data);
                    std::cout << buffer << std::endl;
                }
            }
        }
    }

    if (programType == ProgramType::Client)
    {
        SDLNet_ResolveHost(&ipAddress, getHostname().c_str(), 2000);

        socket = SDLNet_UDP_Open(NULL);
        packet = SDLNet_AllocPacket(512);

        while (!quit)
        {
            system("cls");

            std::string message = "";
            std::cout << "Send a message\n ->";
            std::getline(std::cin, message);

            sprintf(buffer, "%s", message.c_str());

            packet->address.host = ipAddress.host;
            packet->address.port = ipAddress.port;
            packet->data = (Uint8*)buffer;
            packet->len = strlen(message.c_str()) + 1;

            SDLNet_UDP_Send(socket, -1, packet);

            if (message.find("quit") != std::string::npos)
            {
                quit = true;
            }
        }
    }

    packet->data = NULL;

    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(socket);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}