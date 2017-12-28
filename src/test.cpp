#include <iostream>

#include "../include/practicalSocket.h"
#include "practicalSocket.cpp"




int main(){
            std::string msg("GET /\n");
            char buffer[1024];
            TCPSocket sock("www.wp.pl", 80);

            sock.send(msg.c_str(),msg.length());
            sock.recv(buffer, 1023);
            std::cout<< buffer << std::endl;


    return 0;
}
