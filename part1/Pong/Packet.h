
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

#define BUFFER_MAX 512

// The data that the packet will have
struct PacketString {
	const char * data;
	unsigned int len;
	unsigned int host;
	unsigned int port;
};

// This is a class which represents a packet send from 2 network components
class Packet {
private:
	// The packets size
	size_t packetSize;
	// The packets data
	PacketString packetData;
	// A pointer to the actually object
	UDPpacket* packet;
	// a buffer for grabbing and converting data
	char buffer[BUFFER_MAX];
public:
	// Constructor & Deconstructor
	Packet();
	~Packet();

	// inserts data into the packet and sets its destination
	UDPpacket * insertString(int host, int port, std::string data);
	// sets the packet size
	bool setSize(unsigned int packetSize);
	// grabs the data from the packet
	void readPacketData();
	
	// get the packets raw object
	UDPpacket* getClass();
	// get the data from the packet
	PacketString& getData();
	// get the size of the packet
	size_t getSize();
};