#ifndef __BEHOLDER_CPP__
#define __BEHOLDER_CPP__

#include <thread>
#include <iostream>
#include <mutex>
#include <deque>
#include <ctime>
#include <string>
#include <sstream>

#include "../include/datatypes.hpp"
#include "../lib/practicalSocket.h"

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

        //ture - stopped, false - working
        bool _stop_thread;

        Request _r;

        void observe(std::deque<Report>& overseerMsgQueue, /*std::condition_variable& overseerCondVar,*/ std::mutex& overseerMutex){
            //std::cout << "Port: " << _r.port << std::endl;
            std::string protocolRequest("GET /\n");
            char buffer[1024];
            while(!_stop_thread){
                std::this_thread::sleep_for(std::chrono::seconds(_r.interval));
                std::string connectionResult;
                try{
                    TCPSocket sock(_r.ip, static_cast<int>(_r.port));

                    sock.send(protocolRequest.c_str(), protocolRequest.length());
                    std::size_t recievedDataSize = 0;
                    recievedDataSize = sock.recv(buffer, 1023);
                    if(recievedDataSize > 0){
                        connectionResult = buffer;
                    } else {
                        connectionResult = "Connection established, but recieved 0 bytes.";
                    }
                } catch (const SocketException& e) {
                    connectionResult = e.what();
                }
                Report error(_r);
                error.event_time = std::time(nullptr);

                std::ostringstream oss;
                oss << std::asctime(std::localtime(&error.event_time));
                oss << "Beholder is watching: ";
                oss << _r.ip;
                oss << " ";
                oss << std::to_string(static_cast<int>(_r.port));
                oss << " ";
                oss << connectionResult;
                error.msg = oss.str();

                std::unique_lock<std::mutex> lock(overseerMutex);
                overseerMsgQueue.push_back(error);
                lock.unlock();
                //overseerCondVar.notify_one();
            }
        }
};
#endif
