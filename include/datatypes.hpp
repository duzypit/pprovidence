#ifndef __DATATYPES__
#define __DATATYPES__
#include <string>
#include <chrono>

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
    std::size_t job_id;
    char command;
};

struct Report : public Request {
    std::time_t event_time;
};
