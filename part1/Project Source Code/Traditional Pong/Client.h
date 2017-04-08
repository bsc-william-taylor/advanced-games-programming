
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
#include "Packet.h"

// The state of the client
enum CLIENT_STATE {
	DISCONNECTED, CONNECTED
};

// A client class which will send data to a server
class Client {
private:
	// the size of the packet the client will send
	unsigned int clientPacketSize;
	// the servers hostname to connect to
	std::string server_hostname;
	// the servers IPaddress
	IPaddress serverAddress;
	// the outgoing socket
	UDPsocket outSocket;
	// the packet the client will send
	Packet packet;
public:
	// Constructor & Deconstructor
	Client();
	~Client();
	
	// sets the packet size
	bool setPacketSize(unsigned int);
	// setup port we will export data to
	bool setExportPort(unsigned int);
	// has a packet been recieved
	bool packetRecieved();
	// get the packet that has been sent
	Packet& getPacket();
public:
	// set the destination host name
	void setDestinationHostName(std::string);
	// send this data to the client
	void sendString(std::string);
	// disconnect from the server
	void disconnect();
	// showdown the client
	void shutdown();
	// connect to the server
	void connect();
private:
	// get the clients current state
	CLIENT_STATE getClientState();
	// the state of the client 
	CLIENT_STATE state;
};