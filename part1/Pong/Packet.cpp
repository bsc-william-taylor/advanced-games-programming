
#include "Packet.h"

Packet::Packet()
	: packet(NULL)
{
}

Packet::~Packet()
{
	if (packet != NULL) 
	{
		packet->data = NULL;
		SDLNet_FreePacket(packet);
		packet = NULL;
	}
}

void Packet::readPacketData()
{
	strcpy(buffer, (char*)packet->data);

	packetData.host = packet->address.host;
	packetData.port = packet->address.port;
	packetData.data = buffer;
	packetData.len = packet->len;
}

PacketString& Packet::getData()
{
	return packetData;
}

bool Packet::setSize(unsigned int size)
{
	packetSize = size;
	packet = SDLNet_AllocPacket(size);

	if (packet == NULL)
	{
		throw Error(NETWORKING, SDLNet_GetError(), WILLIAM);

		return (false);
	}

	return (true);
}

UDPpacket* Packet::insertString(int host, int port, std::string str)
{
	if (sprintf(buffer, "%s", str.c_str()) < 0)
	{
		throw Error(NETWORKING, "Failed to write string to buffer packet", WILLIAM);
	}
	else
	{
		packet->address.host = host;
		packet->address.port = port;
		packet->data = (Uint8*)buffer;
		packet->len = strlen(str.c_str()) + 1;
	}

	return packet;
}

UDPpacket* Packet::getClass()
{
	return packet;
}

unsigned int Packet::getSize()
{
	return packetSize;
}
