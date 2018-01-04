#ifndef __BEHOLDER_CPP__
#define __BEHOLDER_CPP__

#include <thread>
#include <iostream>
#include <mutex>
#include <deque>
#include <ctime>
#include <string>
#include <condition_variable>

#include "../include/datatypes.hpp"
#include "../lib/practicalSocket.h"
#include "protocolMinion.hpp"

class Beholder{
    public:
    Beholder(Request r) : _thread(), _stop_thread(true), _r(r) {}
    ~Beholder(){
        _stop_thread = true;
        if(_thread.joinable()) {
            _thread.join();
            std::cout << "Beholder joined!" << std::endl;
        }
    }

    Beholder(const Beholder&) = delete;
    Beholder(Beholder &&) = delete;

    void start(std::deque<Report>& overseerMsgQueue, std::condition_variable& overseerCondVar, std::mutex& overseerMutex){
        _stop_thread = false;
        _thread = std::thread(&Beholder::observe, this, std::ref(overseerMsgQueue), std::ref(overseerCondVar), std::ref(overseerMutex));
    }

    void stop(){
        _stop_thread = true;
    }

    std::string ip(){
        return _r.ip;
    }

    int port(){
        return static_cast<int>(_r.port);
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
        std::mutex _beholderMutex;
        std::condition_variable _beholderCondVar;
        //ture - stopped, false - working
        bool _stop_thread;

        Request _r;

        void observe(std::deque<Report>& overseerMsgQueue, std::condition_variable& overseerCondVar, std::mutex& overseerMutex){
            std::string protocolRequest("GET /\n");
            while(!_stop_thread){
                Report error(_r);
               // std::unique_lock<std::mutex> beholderLock(_beholderMutex);
               // _beholderCondVar.wait_for(beholderLock, std::chrono::duration<int>(_r.interval), [this](){return _stop_thread;});
                std::cout << "beholder" << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(_r.interval));
                if(!_stop_thread){
                    ProtocolMinion socket(_r.ip, static_cast<int>(_r.port));
                    error.msg = socket.result();
                    error.event_time = std::time(nullptr);
                    std::unique_lock<std::mutex> lock(overseerMutex);
                    overseerMsgQueue.push_back(error);
                    lock.unlock();
                    overseerCondVar.notify_one();
                }
            }
        }
};
#endif
