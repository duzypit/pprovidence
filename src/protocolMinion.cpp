#include "../include/protocolMinion.hpp"
ProtocolMinion::ProtocolMinion(std::string address, int port, int timeoutSec, int timeoutUsec)
{
    switch(port)
    {
        case 80:
            _requestCommand = "GET /\n";
            break;
        default:
            _requestCommand = "";

    }

    try
    {
        char buffer[1024];
        TCPSocket sock;

        sock.setSendTimeout(timeoutSec, timeoutUsec);
        sock.connect(address, port);

        if (!_requestCommand.empty())
        {
            sock.send(_requestCommand.c_str(), _requestCommand.length());
        }

        std::size_t recievedDataSize = 0;
        recievedDataSize = sock.recv(buffer, 1023);
        buffer[1023] = '\0';

        if(recievedDataSize > 0)
        {
            _msg.first = false;
            _msg.second = "Connection OK. ";
            _msg.second += std::string("Recieved ") + std::to_string(recievedDataSize) + std::string(" bytes.");
        } else
        {
            _msg.first = false;
            _msg.second = "Connection established, recieved 0 bytes.";
        }

    } catch (const SocketException& e) {
        _msg.first = true;
        _msg.second = e.what();
    }
}

ProtocolMinion::~ProtocolMinion(){}

std::pair<bool, std::string> ProtocolMinion::result(){
    return _msg;
}

std::string ProtocolMinion::removeLastChar(std::string s) {
    if (!s.empty()){
        s.pop_back();
    }
    return s;
}
