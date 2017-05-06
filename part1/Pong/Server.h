
#pragma once

#include "MajorInclude.h"
#include "Client.h"
#include "Packet.h"

struct ConnectedClient 
{
	std::string hostname;	
	UDPsocket outSocket;	
	IPaddress address;		
};

struct DisconnectedClient 
{
	std::string time;		
	IPaddress ip;			
};

class Server
{
	std::vector<DisconnectedClient> inactiveClients;
	std::vector<ConnectedClient> activeClients;

	IPaddress serverAddress;
	UDPsocket serverSocket;
	Packet packet;
public:
	Server();
	~Server();

	bool setPacketSize(unsigned int);
	bool setImportPort(unsigned int);
	bool packetRecieved();

	void sendString(std::string);
	void shutdown();

	Packet& getPacket();
};