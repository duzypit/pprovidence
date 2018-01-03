#ifndef __PROTOCOL_MINION_HPP__
#define __PROTOCOL_MINION_HPP__
#include <string>

#include "../lib/practicalSocket.h"

class ProtocolMinion{
public:
    ProtocolMinion(std::string address, int port, int timeoutSec = 2, int timeoutUsec = 0) {
        switch(port){
            //no need for comand 20/ftp,
            // 25/smtp also
            //
            case 80:
                _requestCommand = "GET /\n";
                break;
            case 22:
                //line must be terminated by CR LF
                _requestCommand = "SSH-2.0-billsSSH_3.6.3q3\r\n";
            default:
                _requestCommand = "";

        }

        try{
            char buffer[1024];
            TCPSocket sock(address, port);
            sock.setSendTimeout(timeoutSec, timeoutUsec);
            sock.send(_requestCommand.c_str(), _requestCommand.length());
            std::size_t recievedDataSize = 0;
            recievedDataSize = sock.recv(buffer, 1023);
            buffer[1023] = '\0';

            if(recievedDataSize > 0){
                _msg = "Connection OK. ";
                _msg += removeLastChar(std::string(buffer));
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

    std::string removeLF(std::string s){
        if(!s.empty()){
            s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        }

        return s;
    }

    std::string removeLastChar(std::string s) {
        if (!s.empty()){
            s.pop_back();
        }
        return s;
    }
};

#endif
