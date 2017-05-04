
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

#ifndef __NETWORK__H_
#define __NETWORK__H_

// include all network components for the user
#include "Client.h"
#include "Packet.h"
#include "Server.h"

// include these standard headers
#include <sstream>
#include <string>

// set some macros to tell the user about defaults
#define DEFAULT_PORT 2000
#define DEFAULT_SIZE 50
#define PACKET_MAX 512
#define PACKET_MIN 1

// global function to aquire the hostname
std::string getHostname();

#endif
