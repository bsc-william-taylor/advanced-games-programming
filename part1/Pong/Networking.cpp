
#include "Networking.h"

std::string getHostname()
{
    std::stringstream ss;
    char temp[100];
    gethostname(temp, 100);
    ss << temp;
    return ss.str();
}
