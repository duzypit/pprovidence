#ifndef __PROTOCOL_MINION_HPP__
#define __PROTOCOL_MINION_HPP__
#include <string>

#include "../lib/practicalSocket.h"

class ProtocolMinion
{
public:
    ProtocolMinion(std::string address, int port, int timeoutSec = 2, int timeoutUsec = 0);
    ~ProtocolMinion();

    std::pair<bool, std::string> result();

private:
    std::pair<bool, std::string> _msg;
    std::string _requestCommand;

    std::string removeLastChar(std::string s);
};

#endif
