
#include "Client.h"

Client::Client()
    : outSocket(NULL)
{
}

Client::~Client()
{
    shutdown();
}

void Client::shutdown()
{
    if (outSocket != NULL)
    {
        SDLNet_UDP_Close(outSocket);
        outSocket = NULL;
    }
}

bool Client::setPacketSize(unsigned int size)
{
    clientPacketSize = size;

    if (!packet.setSize(clientPacketSize))
    {
        throw Error(NETWORKING, "Couldnt allocate memory for packet", WILLIAM);
    }

    return true;
}

CLIENT_STATE Client::getClientState()
{
    return state;
}

bool Client::setExportPort(unsigned int port)
{
    if (!(outSocket = SDLNet_UDP_Open(NULL)))
    {
        throw Error(GAME, SDLNet_GetError(), WILLIAM);
    }

    if (SDLNet_ResolveHost(&serverAddress, serverHostname.c_str(), port) != 0)
    {
        throw Error(GAME, SDLNet_GetError(), WILLIAM);
    }

    return true;
}

bool Client::packetRecieved()
{
    if (SDLNet_UDP_Recv(outSocket, packet.getClass()))
    {
        packet.readPacketData();
        return true;
    }
    else
    {
        return false;
    }
}

Packet& Client::getPacket()
{
    return packet;
}

void Client::connect()
{
    if (outSocket)
    {
        sendString("+client:");
    }
    else
    {
        throw Error(NETWORKING, "Outsocket isnt setup to send connect command", WILLIAM);
    }
}

void Client::disconnect()
{
    if (outSocket)
    {
        sendString("-client:");
    }
    else
    {
        throw Error(NETWORKING, "Outsocket isnt setup to send disconnect command", WILLIAM);
    }
}

void Client::setDestinationHostName(std::string nm)
{
    serverHostname = nm;
}

void Client::sendString(std::string str)
{
    if (outSocket)
    {
        if (!str.empty())
        {
            SDLNet_UDP_Send(outSocket, -1, packet.insertString(
                serverAddress.host, serverAddress.port,
                str)
            );
        }
        else
        {
            throw Error(NETWORKING, "string is empty we cannot send a packet with no data", WILLIAM);
        }
    }
    else
    {
        throw Error(NETWORKING, "outsocket has not been set up therefore we cannot send the string", WILLIAM);
    }
}