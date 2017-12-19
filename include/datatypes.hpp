#ifndef __DATATYPES__
#define __DATATYPES__
#include <string>

enum class Protocol {
    ftp=20,
    ssh = 22,
    smtp=25,
    http = 80,
    pop3=110
};

struct Request{

    std::string ip;
    std::string email;
    int interval;
    int port;
    int job_id;
    char command;
};

#endif
