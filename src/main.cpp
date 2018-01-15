#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>

#include "../include/datatypes.hpp"
#include "../include/commandParser.hpp"
#include "../include/overseer.hpp"
#include "../include/beholder.hpp"
#include "../include/scribe.hpp"
#include "../lib/practicalSocket.h"
#include "../include/protocolMinion.hpp"
#include "../include/commandLoader.hpp"
#include "../include/passwd.hpp"
#include "../include/smtpSender.hpp"



int main(int argc, char* argv[])
{

    Overseer master("log.txt");
    CommandParser cparser;
    GmailCreditenials gmailCreditenials;
    std::cout << std::string(80, '\n');

    if(argc >= 2)
    {
        //load hosts file
        CommandLoader hl(argv[1]);
        std::vector<std::string> requests;
        requests = hl.requestsVector();
        for(auto r : requests)
        {
            cparser.parse(r);
            if(cparser.valid())
            {
                master.dispatch(cparser.req_struct());
            }
        }
    }

    std::string command;

    std::cout << "Type a command (q - quit, ? - help)." << std::endl;
    for(;;)
    {
        std::cout << ">:";
        command.clear();

        std::getline(std::cin, command);
        if(command == "?")
        {
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "\ta <adress> <20|21|22|25|80|110|995> <interval> <email> - add adress to watch, interval in seconds" << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\ts <job_id> - stop job" << std::endl;
            std::cout << "\tr <job_id> - run again job" << std::endl;
            std::cout << "\tc - fill creditenials to Gmail accout for email notification sending" << std::endl;
            std::cout << std::endl;
        }
        else if(command == "c")
        {
            Passwd p;
            SMTPSender sender;

            std::cout << "Gmail username >: ";
            std::cin >> gmailCreditenials.uname;

            std::cout << "Gmail password >: ";
            gmailCreditenials.password = p.getPassword();
            std::cout << std::endl;

            if (sender.verifyCreditenials(gmailCreditenials.uname, gmailCreditenials.password))
            {
                gmailCreditenials.valid = true;
                master.setUpMailer(gmailCreditenials);
                std::cout << "Gmail creditenials valid" << std::endl;

            }
            else
            {
                gmailCreditenials.valid = false;
                gmailCreditenials.uname.clear();
                gmailCreditenials.password.clear();
                std::cout<<"Gmail creditenials invalid!" << std::endl;
            }
        }
        else if(command == "q")
        {
            std::cout << "Bye!" << std::endl;
            break;
        } else
        {
            if(!command.empty())
            {
                cparser.parse(command);
                if(cparser.valid())
                {
                    master.dispatch(cparser.req_struct());
                }
            }
        }

    }
    return 0;
}
