#include "../include/smtpSocket.hpp"
SMTPSocket::SMTPSocket(const std::string& address, const int& port)
{
    socket_.connect(address, port);
}

Socket* SMTPSocket::GetSocket()
{
    return &socket_;
}

