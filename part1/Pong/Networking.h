
#pragma once

#include "Client.h"
#include "Packet.h"
#include "Server.h"

#include <sstream>
#include <string>

#define DEFAULT_PORT 2000
#define DEFAULT_SIZE 50
#define PACKET_MAX 512
#define PACKET_MIN 1

std::string getHostname();

