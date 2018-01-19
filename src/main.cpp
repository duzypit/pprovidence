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
#include <stdlib.h> //for readline
#include <readline/readline.h>
#include <readline/history.h>


int main()
{

    Overseer master;
    CommandParser cparser;
    GmailCredentials gmailCredentials;
	rl_bind_key('\t', rl_insert);

    std::cout << std::string(80, '\n');

    //load cfg file hosts file
    CommandLoader hl("pprovidence.cfg");
    std::vector<std::string> requests;
    requests = hl.requestsVector();
    for(auto r : requests)
    {

        cparser.parse(r, false);
        if(cparser.valid())
        {
            master.dispatch(cparser.req_struct());
        }
    }

    std::string command;
    std::cout << "Project Providence (all-seeing eye) - monitoring of remote hosts in time." << std::endl;
    std::cout << "Type a command (q - quit, ? - help)." << std::endl;
	char* buf;
    while ((buf = readline(">: ")) != nullptr)
    {
        if(strlen(buf) > 0)
        {
            add_history(buf);
        }

        command.clear();
        command = buf;
        free(buf);

        //std::getline(std::cin, command);
        if(command == "?")
        {
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "\ta <adress> <20|21|22|25|80|110|995> <interval> <email> - add adress to watch, interval in seconds" << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\ts <job_id> - stop selected job" << std::endl;
            std::cout << "\tr <job_id> - run selected job again" << std::endl;
            std::cout << "\tc - fill credentials to Gmail accout for email notification sending" << std::endl;
            std::cout << "\tq - quit" << std::endl;
            std::cout << std::endl;
        }
        else if(command == "c")
        {
            Passwd p;
            SMTPSender sender;

            std::cout << "Gmail username >: ";
            std::cin >> gmailCredentials.uname;

            std::cout << "Gmail password >: ";
            gmailCredentials.password = p.getPassword();
            std::cout << std::endl;

            if (sender.verifyCreditenials(gmailCredentials.uname, gmailCredentials.password))
            {
                gmailCredentials.valid = true;
                master.setUpMailer(gmailCredentials);
                std::cout << "Gmail credentials valid" << std::endl;

            }
            else
            {
                gmailCredentials.valid = false;
                gmailCredentials.uname.clear();
                gmailCredentials.password.clear();
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
