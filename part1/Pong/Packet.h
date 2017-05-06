
#pragma once

#include "MajorInclude.h"

struct PacketString
{
    const char * data;
    unsigned int len;
    unsigned int host;
    unsigned int port;
};

class Packet
{
    size_t packetSize;
    PacketString packetData;
    UDPpacket* packet;
    char buffer[512];
public:
    Packet();
    ~Packet();

    UDPpacket* insertString(int host, int port, std::string data);
    bool setSize(unsigned int packetSize);
    void readPacketData();

    UDPpacket* getClass();
    PacketString& getData();
    size_t getSize();
};