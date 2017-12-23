#ifndef __SCRIBE_HPP__
#define __SCRIBE_HPP__
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <deque>
#include <thread>
//#include <condition_variable>

#include "../include/datatypes.hpp"

class Scribe{
public:
    Scribe(const std::string& file) : _file(file.c_str(), std::ios::ate) {}

    ~Scribe(){
        _stop_thread = true;
        if (_thread.joinable()) {
            std::cout << "Scribe.join()" << std::endl;
            _thread.join();
            std::cout << "Scribe joined!" << std::endl;
        }
        _file.close();
    }

    void start(std::deque<Report>& overseerMsgQueue,/* std::condition_variable& overseerCondVar,*/  std::mutex& overseerMutex){
        _stop_thread = false;
        _thread = std::thread(&Scribe::observe, this, std::ref(overseerMsgQueue),/* std::ref(overseerCondVar),*/ std::ref(overseerMutex));
    }

    //save smtn to file
    void save(const Report& e){
        _file << e.msg << std::endl;
    }

private:
    std::ofstream _file;
    std::thread _thread;
    bool _stop_thread;

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
            //write to file
        }

    }
};

#endif
