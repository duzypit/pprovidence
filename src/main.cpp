
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
            std::cout << "\ta ip port interval(seconds) email - add a service to watch " << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\td job_id - delete job" <<std::endl;
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
