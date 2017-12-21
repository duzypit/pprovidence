#ifndef __BEHOLDER_CPP__
#define __BEHOLDER_CPP__

#include <thread>
#include <iostream>
#include <mutex>
#include <deque>
#include <chrono>

#include "../include/datatypes.hpp"

class Beholder{
    public:
    Beholder(Request r) : _thread(), _stop_thread(true), _r(r) {}
    ~Beholder(){
        _stop_thread = true;
        if(_thread.joinable()) _thread.join();
    }

    Beholder(const Beholder&) = delete;
    Beholder(Beholder &&) = delete;

    void start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex){
        _stop_thread = false;
        _thread = std::thread(&Beholder::observe, this, std::ref(overseerMsgQueue), std::ref(overseerMutex));
    }

    void stop(){
        _stop_thread = true;
    }

    std::string ip(){
        return _r.ip;
    }

    int port(){
        return _r.port;
    }

    int interval(){
        return _r.interval;
    }

    std::string email(){
        return _r.email;
    }

    bool stopped(){
        return _stop_thread;
    }

    private:
        std::thread _thread;

        //ture - stopped, false - working
        bool _stop_thread;

        Request _r;

        void observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex){
            while(!_stop_thread){
                std::this_thread::sleep_for(std::chrono::seconds(_r.interval));
                //create queue entry
                //lock
                Report error(_r);
                //std::string msg;
                error.event_time = std::chrono::now;
                error.msg =  "Beholder: watching: " + _r.ip + " " + _r.port;
                std::lock_guard<std::mutex> guard(overseerMutex);
                overseerMsgQueue.push_back(error);
            }
        }
};
#endif
