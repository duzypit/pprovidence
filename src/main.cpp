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
#include "../include/commandLoader.hpp"

int main(int argc, char* argv[]){

    Overseer master("log.txt");
    commandParser cparser;

    std::cout << std::string(80, '\n');

    if(argc >= 2){
        //load hosts file
        CommandLoader hl(argv[1]);
        std::vector<std::string> requests;
        requests = hl.requestsVector();
        for(auto r : requests){
            cparser.parse(r);
            if(cparser.valid()){
                master.dispatch(cparser.req_struct());
            }
        }
    }

    std::string command;

    std::cout << "Type a command (q - quit, ? - help)." << std::endl;
    for(;;){
        std::cout << ">:";
        command.clear();

        std::getline(std::cin, command);
        if(command == "?"){
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "\ta <adress> <20|21|22|25|80|110|995> <interval> <email> - add adress to watch, interval in seconds" << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\ts <job_id> - stop job" <<std::endl;
            std::cout << std::endl;
        } else if(command == "q") {
            return 0;
        } else {
            cparser.parse(command);
            if(cparser.valid()){
                master.dispatch(cparser.req_struct());
            }
        }

    }
    return 0;
}
