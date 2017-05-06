
#include "Server.h"

// Constructor & Deconstructor
Server::Server()
	: serverSocket(NULL)
{
}

Server::~Server()
{
	// if we have an active server socket
	if (serverSocket != NULL) 
	{
		// close the socket
		SDLNet_UDP_Close(serverSocket);
		serverSocket = NULL;
	}
}


// sets the size of the packet to be sent in bytes
bool Server::setPacketSize(unsigned int sz)
{
	return packet.setSize(sz);
}

// returns a reference to the packet
Packet& Server::getPacket()
{
	return packet;
}

bool Server::setImportPort(unsigned int port)
{
	// if the socket has been created already
	if (serverSocket == NULL)
	{
		// open up the socket on the specified port
		serverSocket = SDLNet_UDP_Open(port);

		// if we havent successfully opened the port
		if (!serverSocket) {
			// throw a networking error
			throw Error(NETWORKING, SDLNet_GetError(), WILLIAM);
			// and return false to the user
			return false;
		}
	}
	else
	{
		// if the socket has already been initialised throw an error
		throw Error(NETWORKING, "You tired to open a port on a already opened port", WILLIAM);
	}

	// return true to indicate function success
	return true;
}

// sends a string to all clients
void Server::sendString(std::string str)
{
	// for each client in the activeClients vector
	for (auto&& client : activeClients) {
		// send the message to them
		SDLNet_UDP_Send(client.outSocket, -1, packet.insertString(
			client.address.host, client.address.port,
			str.c_str())
		);
	}
}

// Shutsdown the port and all clientrs
void Server::shutdown()
{
	// clear the 
	inactiveClients.clear();
	activeClients.clear();

	// close the socket
	SDLNet_UDP_Close(serverSocket);
	// and make the pointer null
	serverSocket = NULL;
}

bool Server::packetRecieved()
{
	// if a packet has been recieved
	if (SDLNet_UDP_Recv(serverSocket, packet.getClass())) 
	{
		// grab the packet data
		packet.readPacketData();

		std::string command = packet.getData().data;
		
		// if we recieved a all client command
		if (command.find("+client:") != std::string::npos) 
		{
			// add the client information to the list of acive clients
			ConnectedClient client;
		
			client.address.host = packet.getData().host;
			client.address.port = packet.getData().port;

			// get the hostname as well
			const char * host;
			if (!(host = SDLNet_ResolveIP(&client.address))) 
			{
				// if we cant get the host name throw an error
				throw Error(NETWORKING, SDLNet_GetError());
			}

			// set the hostname
			client.hostname = std::string(host);

			// open a client socket
			client.outSocket = SDLNet_UDP_Open(client.address.port);
			if (!client.outSocket) 
			{
				// throw an error if we cant open the port
				throw Error(NETWORKING, SDLNet_GetError());
			}

			// push back the client info into the vector
			activeClients.push_back(client);
		}

		// if we have a remove command
		if (command.find("-client:") != std::string::npos) {
			// find the client
			for (int i = 0; i < activeClients.size(); i++) {
				if (packet.getData().host == activeClients[i].address.host) {
					// and add its inforamation into the inactive clients list
					DisconnectedClient disconnectedClient;
					disconnectedClient.ip = activeClients[i].address;
					disconnectedClient.time = "N/A";

					inactiveClients.push_back(disconnectedClient);
				}
			}
		}

		// return true to indicate a packet has been recieved
		return true;
	}

	// return false to indicate a packet hasnt been recieved
	return false;
}