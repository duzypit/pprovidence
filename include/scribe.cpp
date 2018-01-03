#ifndef __SCRIBE_HPP__
#define __SCRIBE_HPP__
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <deque>
#include <thread>
//#include <condition_variable>
#include <sstream>
#include <iomanip> //std::put_time

#include "../include/datatypes.hpp"

class Scribe{
public:
    Scribe(const std::string& file) : _file(file.c_str(), std::ios::ate) {}

    ~Scribe(){
        _stop_thread = true;
        if (_thread.joinable()) {
            _thread.join();
            std::cout << "Scribe joined!" << std::endl;
        }
        _file.close();
    }

    void start(std::deque<Report>& overseerMsgQueue,/* std::condition_variable& overseerCondVar,*/  std::mutex& overseerMutex){
        _stop_thread = false;
        _thread = std::thread(&Scribe::observe, this, std::ref(overseerMsgQueue),/* std::ref(overseerCondVar),*/ std::ref(overseerMutex));
    }

private:
    std::ofstream _file;
    std::thread _thread;
    bool _stop_thread;

    void save(const Report& e){
        _file << formatMsg(e) << std::endl;
    }


    std::string formatMsg(const Report& e){
        std::string msg;
                std::ostringstream oss;
                std::tm tm = *std::localtime(&e.event_time);
                oss << std::put_time(&tm, "%F %T");
                oss << " ";
                oss << e.ip;
                oss << " ";
                oss << std::to_string(static_cast<int>(e.port));
                oss << " ";
                oss << e.msg;
                msg = oss.str();
        return msg;
    }

    void observe(std::deque<Report>& overseerMsgQueue, /*std::condition_variable& overseerCondVar,*/ std::mutex& overseerMutex){
        Report e;
        while(!_stop_thread){
            std::unique_lock<std::mutex> lock(overseerMutex);
            //overseerCondVar.wait(lock);
            if(!overseerMsgQueue.empty()){
                e = overseerMsgQueue[0];
                overseerMsgQueue.pop_front();
                lock.unlock();
                save(e);
            }
        }
    }
};

#endif
