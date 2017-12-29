#ifndef __PROTOCOL_MINION_HPP__
#define __PROTOCOL_MINION_HPP__
#include <string>

#include "../lib/practicalSocket.h"

class ProtocolMinion{
public:
    ProtocolMinion(std::string address, int port) {
        switch(port){
            case 80:
                _requestCommand = "GET /\n";
                break;
            default:
                _requestCommand = "";

        }

        try{
            char buffer[1024];
            TCPSocket sock(address, port);

            sock.send(_requestCommand.c_str(), _requestCommand.length());
            std::size_t recievedDataSize = 0;
            recievedDataSize = sock.recv(buffer, 1023);
            buffer[1023] = '\0';

            if(recievedDataSize > 0){
                _msg = "Connection OK.";
            } else {
                _msg = "Connection established, recieved 0 bytes.";
            }
        } catch (const SocketException& e) {
            _msg = e.what();
        }
    }

    ~ProtocolMinion(){}

    std::string result(){
        return _msg;
    }
private:
    std::string _msg;
    std::string _requestCommand;
};

#endif
