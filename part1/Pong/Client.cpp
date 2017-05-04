
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

#include "Client.h"

// Constructor & Deconstructor
Client::Client()
	: outSocket(NULL)
{
}

Client::~Client()
{
	// call shutdown just in case the user hasnt
	shutdown();
}

// Shutsdown the clients port available to other processes
void Client::shutdown()
{
	// if the out socket is active
	if (outSocket != NULL) 
	{
		// close it 
		SDLNet_UDP_Close(outSocket);
		// and make the pointer NULL
		outSocket = NULL;
	}
}

// sets the size of the packet that will be sent
bool Client::setPacketSize(unsigned int size)
{
	// keep a record of the packet size 
	clientPacketSize = size;
	
	// if the set function fails
	if (!packet.setSize(clientPacketSize))
	{
		// throw an error
		throw Error(NETWORKING, "Couldnt allocate memory for packet", WILLIAM);

		// return false to show the function failed
		return false;
	}

	// return true to show the function succeeded
	return true;
}

// returns the current state of the client
CLIENT_STATE Client::getClientState()
{
	return state;
}

// setup the socket which will export data and the port which the server will recieve data
bool Client::setExportPort(unsigned int port)
{
	// open a available port and if we fail
	if (!(outSocket = SDLNet_UDP_Open(NULL)))
	{
		// throw an exception
		throw Error(GAME, SDLNet_GetError(), WILLIAM);

		// return false to indicate function fail
		return false;
	}

	// get the address of the server
	if (SDLNet_ResolveHost(&serverAddress, server_hostname.c_str(), port) != 0) 
	{
		// on fail throw an error
		throw Error(GAME, SDLNet_GetError(), WILLIAM);

		// return false to indicate function fail
		return false;
	}

	// return false to indicate function success
	return true;
}

// a check function to tell the user if a packet has been recieved
bool Client::packetRecieved()
{
	// see if a pack has been recieved if so
	if (SDLNet_UDP_Recv(outSocket, packet.getClass())) 
	{
		// read packet data and return true
		packet.readPacketData();
		return true;
	}
	else
	{
		return false;
	}
}

// returns the packet to be sent
Packet& Client::getPacket()
{
	return packet;
}

// sends a connect command to the server
void Client::connect()
{
	// if the outsocket has be setup
	if (outSocket)
	{
		// set the disconnect command
		sendString("+client:");
	}
	else
	{
		// else throw an exception
		throw Error(NETWORKING, "Outsocket isnt setup to send connect command", WILLIAM);
	}
}

// send s a disconnect command to the server
void Client::disconnect()
{
	// if the outsocket has be setup
	if (outSocket)
	{
		// set the disconnect command
		sendString("-client:");
	}
	else
	{
		// else throw an exception
		throw Error(NETWORKING, "Outsocket isnt setup to send disconnect command", WILLIAM);
	}
}

// sets the hostname of the server we will connect to
void Client::setDestinationHostName(std::string nm)
{
	server_hostname = nm;
}

// sends a string of data to the client
void Client::sendString(std::string str)
{
	// if the outsocket is ready
	if (outSocket)
	{
		// and the string has valid data
		if (!str.empty()) 
		{
			// send the packet to the server
			SDLNet_UDP_Send(outSocket, -1, packet.insertString(
				serverAddress.host, serverAddress.port,
				str)
			);
		}
		else
		{
			// else throw error
			throw Error(NETWORKING, "string is empty we cannot send a packet with no data", WILLIAM);
		}
	}
	else
	{
		// else throw error
		throw Error(NETWORKING, "outsocket has not been set up therefore we cannot send the string", WILLIAM);
	}
}