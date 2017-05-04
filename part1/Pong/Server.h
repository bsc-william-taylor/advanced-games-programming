

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

#pragma once

#include "CommonHeader.h"
#include "Client.h"
#include "Packet.h"

// a struct for Connected client information
struct ConnectedClient {
	std::string host_name;	// the hosts name as a string
	UDPsocket outSocket;	// the socket to send messages back
	IPaddress address;		// the IPaddress for the client
};

// a struct for Disconnected client information
struct DisconnectedClient {
	std::string time;		// The time it disconnected
	IPaddress ip;			// The IPaddress
};

// The server class which handles clients and sends messages to them
class Server {
private:
	// a vector of active and inactive clients
	std::vector<DisconnectedClient> inactiveClients;
	std::vector<ConnectedClient> activeClients;
private:
	// the servers IP address
	IPaddress serverAddress;
	// the incoming port
	UDPsocket serverSocket;
	// the incoming packet
	Packet packet;
public:
	// Constructor & Deconstructor
	Server();
	~Server();

	// sets the packet size
	bool setPacketSize(unsigned int);
	// set the packets size
	bool setImportPort(unsigned int);
	// returns true if the packet wqas recieved
	bool packetRecieved();

	// sends a string to all clients
	void sendString(std::string);
	// shutsdown the server and releases the port
	void shutdown();
	// returns the sended packet
	Packet& getPacket();
};