
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

// lots of little functions to help setting up the lab
#include "lab_main.h"

int main(int argc, char * argv[])
{
	// setup all the libraries
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

	// gets the type of network program you want to run
	ProgramType programType = selectProgramType();

	// the server we will send messages to
	IPaddress serverAddress;
	// the packet that will either be sent or recieved
	UDPpacket* packet;
	// the outgoing/incoming socket
	UDPsocket socket;
	// a buffer for converting data
	char buffer[512];
	// something so we know when to exit
	int quit = 0;

	// If the user selects server start the server app
	if (programType == SERVER)
	{
		// create an incoming socket on port 2000
		socket = SDLNet_UDP_Open(2000);
		// set the size of the packets we will recieve
		packet = SDLNet_AllocPacket(512);

		// enter a loop waiting for messages
		while (!quit)
		{
			// if we recieve a message
			if (SDLNet_UDP_Recv(socket, packet))
			{
				// if its a quit message, quit
				if (strcmp((char*)packet->data, "quit") == 0) 
				{
					quit = true;
				}
				else 
				{
					// else clear the console
					system("cls");
					// copy the string into the buffer
					strcpy(buffer, (char*)packet->data);
					// output the buffer
					std::cout << buffer << std::endl;
				}
			}
		}
	}

	// if the user wants to be the client sending messages
	if (programType == CLIENT)
	{
		// get the address of the server application
		SDLNet_ResolveHost(&serverAddress, getHostname().c_str(), 2000);

		// open up an available port to send packets
		socket = SDLNet_UDP_Open(NULL);
		// allocate memory for the packet we will send
		packet = SDLNet_AllocPacket(512);

		// enter a loop
		while (!quit)
		{
			// clear the console
			system("cls");

			// get a message from the user
			std::string message = "";
			std::cout << "Send a message\n ->";
			std::getline(std::cin, message);
			
			// pack it into the buffer
			sprintf(buffer, "%s", message.c_str());

			// setup the packet information, its destination, size etc
			packet->address.host = serverAddress.host;
			packet->address.port = serverAddress.port;
			packet->data = (Uint8*)buffer;
			packet->len = strlen(message.c_str()) + 1;

			// then send that packet through the socket we set up
			SDLNet_UDP_Send(socket, -1, packet);

			// if the message is quit
			if (message.find("quit") != std::string::npos)
			{
				// exit the application
				quit = true;
			}
		}
	}

	// make sure the buffer isnt deleted as memory hasnt been allocated
	packet->data = NULL;
	
	// release packet and socket
	SDLNet_FreePacket(packet);
	SDLNet_UDP_Close(socket);

    // cleanup libs
    SDLNet_Quit();
    SDL_Quit();
	return 0;
}