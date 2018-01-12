#ifndef __SOCKET_CPP__
#define __SOCKET_CPP__
#include "../lib/practicalSocket.h"


class SMTPSocket
{
public:

    SMTPSocket(const std::string& address, const int& port);

    Socket *GetSocket();

private:
    TCPSocket socket_;
}; // class
#endif
