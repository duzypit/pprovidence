#ifndef __BEHOLDER_HPP__
#define __BEHOLDER_HPP__

#include <thread>
#include <iostream>
#include <mutex>
#include <deque>
#include <ctime>
#include <string>
#include <condition_variable>

#include "datatypes.hpp"
#include "../lib/practicalSocket.h"
#include "protocolMinion.hpp"

class Beholder
{
public:
    Beholder(Request r);

    ~Beholder();

    Beholder(const Beholder&) = delete;

    Beholder(Beholder &&) = delete;

    void start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex);

    void stop();

    void run();

    std::string ip();

    int port();

    int interval();

    std::string email();

    bool lastCheckOk();

    std::time_t lastCheck();

    bool stopped();

private:

    std::thread _thread;
    bool _stop_thread;
    Request _r;
    std::mutex _m;
    std::condition_variable _cv;
    std::time_t _lastCheck;
    bool _lastCheckOk;

    //ture - stopped, false - working
    bool _terminate = false;

    void observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex);
};
#endif
