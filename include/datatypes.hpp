#ifndef __DATATYPES__
#define __DATATYPES__
#include <string>
#include <chrono>

enum class Protocol
{
    ftp = 20,
    ssh = 22,
    smtp = 25,
    http = 80,
    pop3 = 110
};

struct Request
{
    std::string ip;
    std::string email;
    int interval;
    //Protocol port;
    int port;
    std::size_t job_id;
    char command;
    bool valid;
};

struct GmailCredentials
{
    std::string uname;
    std::string password;
    bool valid = false;
};

struct Report : public Request
{
    Report(){}

    Report(const Request& r)
    {
        ip = r.ip;
        email = r.email;
        interval = r.interval;
        port = r.port;
        job_id = r.job_id;
        command = r.command;
    }

    ~Report(){}
    std::time_t event_time;
    //first notify, second msg
    std::pair<bool, std::string> msg;
};
#endif
