#ifndef __PROTOCOL_MINION_HPP__
#define __PROTOCOL_MINION_HPP__
#include <string>

#include "../lib/practicalSocket.h"

class ProtocolMinion
{
public:
    ProtocolMinion(std::string address, int port, int timeoutSec = 2, int timeoutUsec = 0)
    {
        switch(port)
        {
            //no need for comand 20/ftp,
            // 25/smtp also
            //
            case 80:
                _requestCommand = "GET /\n";
                break;
            /*case 22:
                //line must be terminated by CR LF
                _requestCommand = "SSH-2.0-billsSSH_3.6.3q3\r\n";*/
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
                //_msg += removeCRLF(std::string(buffer));
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

    ~ProtocolMinion(){}

    std::pair<bool, std::string> result(){
        return _msg;
    }
private:
    std::pair<bool, std::string> _msg;
    std::string _requestCommand;

    std::string removeCRLF(std::string s){
        if(!s.empty()){
            s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
            s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
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
