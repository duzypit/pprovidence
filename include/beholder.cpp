#ifndef __BEHOLDER_CPP__
#define __BEHOLDER_CPP__

#include <thread>
#include <iostream>
#include <mutex>
#include <deque>
#include <ctime>
#include <string>
#include <sstream>
//#include <condition_variable>

#include "../include/datatypes.hpp"

class Beholder{
    public:
    Beholder(Request r) : _thread(), _stop_thread(true), _r(r) {}
    ~Beholder(){
        _stop_thread = true;
        if(_thread.joinable()) {
            std::cout << "Beholder.join()" << std::endl;
            _thread.join();
            std::cout << "Beholder joinde!" << std::endl;
        }
    }

    Beholder(const Beholder&) = delete;
    Beholder(Beholder &&) = delete;

    void start(std::deque<Report>& overseerMsgQueue,/* std::condition_variable& overseerCondVar,*/ std::mutex& overseerMutex){
        _stop_thread = false;
        _thread = std::thread(&Beholder::observe, this, std::ref(overseerMsgQueue), /*std::ref(overseerCondVar),*/ std::ref(overseerMutex));
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

        void observe(std::deque<Report>& overseerMsgQueue, /*std::condition_variable& overseerCondVar,*/ std::mutex& overseerMutex){
            while(!_stop_thread){
                std::this_thread::sleep_for(std::chrono::seconds(_r.interval));
                Report error(_r);
                error.event_time = std::time(nullptr);

                std::ostringstream oss;
                oss << std::asctime(std::localtime(&error.event_time));
                oss << "Beholder: watching: ";
                oss << _r.ip;
                oss << " ";
                oss << std::to_string(_r.port);
                error.msg = oss.str();

                std::unique_lock<std::mutex> lock(overseerMutex);
                overseerMsgQueue.push_back(error);
                lock.unlock();
                //overseerCondVar.notify_one();
            }
        }
};
#endif
