
#pragma once

#include "MajorInclude.h"
#include "Packet.h"

enum CLIENT_STATE
{
    DISCONNECTED, CONNECTED
};

class Client
{
    unsigned int clientPacketSize;
    std::string serverHostname;
    IPaddress serverAddress;
    UDPsocket outSocket;
    Packet packet;
    CLIENT_STATE state;
public:
    Client();
    ~Client();

    bool setPacketSize(unsigned int);
    bool setExportPort(unsigned int);
    bool packetRecieved();

    CLIENT_STATE getClientState();

    void setDestinationHostName(std::string);
    void sendString(std::string);
    void disconnect();
    void shutdown();
    void connect();

    Packet& getPacket();
};