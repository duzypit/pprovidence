
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>

#include "../include/datatypes.hpp"
#include "../include/commandParser.hpp"
#include "../include/overseer.hpp"
#include "../include/beholder.cpp"
#include "../include/scribe.cpp"
#include "../lib/practicalSocket.h"
#include "../include/protocolMinion.hpp"

int main(){
    //google
    //Request r1 = {std::string("172.217.16.3"), std::string("tp@gmail.com"), 3, 80};
    //std::cout << "Create Master" << std::endl;
    //Beholder Master(r1);
    //Request r2 = {std::string("127.0.0.123"), std::string("tp@gmail.com"), 5, 125};
    //Master.add(r2);
    Overseer master("log.txt");
    std::string command;

    std::cout << std::string(80, '\n');
    std::cout << "Type a command (q - quit, ? - help)." << std::endl;
    commandParser cparser;
    for(;;){
        std::cout << ">:";
        command.clear();

        std::getline(std::cin, command);
        if(command == "?"){
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "\ta <adress> <20|22|25|80|110> <interval> <email> - add adress to watch, interval in seconds" << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\ts <job_id> - stop job" <<std::endl;
            std::cout << std::endl;
        } else if(command == "q") {
            return 0;
        } else {
            cparser.parse(command);
            master.dispatch(cparser.req_struct());
        }

    }
    return 0;
}
