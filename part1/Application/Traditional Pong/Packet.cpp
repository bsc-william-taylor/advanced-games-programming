
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

#include "Packet.h"

// Constructor & Deconstructor
Packet::Packet()
	: packet(NULL)
{
}

Packet::~Packet()
{
	// if the packet has been allocated
	if (packet != NULL) 
	{
		// set the data to NULL
		packet->data = NULL;
		// free the packet
		SDLNet_FreePacket(packet);
		// make the pointer NULL
		packet = NULL;
	}
}

// Reads the data from the last recieved packetm
void Packet::readPacketData()
{
	// copy the data into a buffer
	strcpy(buffer, (char*)packet->data);

	// then set the packetData struct data
	packetData.host = packet->address.host;
	packetData.port = packet->address.port;
	packetData.data = buffer;
	packetData.len = packet->len;
}

// Returns the struct with all the packet data
PacketString& Packet::getData()
{
	return packetData;
}

// sets the size of incoming packets
bool Packet::setSize(unsigned int size)
{
	packetSize = size;
	packet = SDLNet_AllocPacket(size);

	// if the packet fail to allocate
	if (packet == NULL)
	{
		// throw an exception to tell the user
		throw Error(NETWORKING, SDLNet_GetError(), WILLIAM);

		// return false to indicate function failure
		return (false);
	}

	// return true to indicate function success
	return (true);
}

// inserts the string into a packet and prepares it for sending
UDPpacket* Packet::insertString(int host, int port, std::string str)
{
	// copy the string into out buffer
	if (sprintf(buffer, "%s", str.c_str()) < 0)
	{
		// if we fail alert the programmer this should never happen though
		throw Error(NETWORKING, "Failed to write string to buffer packet", WILLIAM);
	}
	else
	{
		// set the destination of the packet
		packet->address.host = host;
		packet->address.port = port;

		// then set the packets data and the amount of data to be sent
		packet->data = (Uint8*)buffer;
		packet->len = strlen(str.c_str()) + 1;
	}

	// return the packet for sending
	return packet;
}

// get the raw packet class
UDPpacket* Packet::getClass()
{
	return packet;
}

// return the size of the memory allocated to the packet
unsigned int Packet::getSize()
{
	return packetSize;
}
