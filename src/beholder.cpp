#ifndef __BEHOLDER_HPP__
#define __BEHOLDER_HPP__

#include <string>
#include <thread>
#include <iostream>

class Beholder{
public:
    Beholder(){};

    Beholder(std::string ip, int port, int interval, std::string email) : _ip(ip), _port(port), _interval(interval), _email(email){
        //setup
        //create protocol minion
        //start observation
        //signal success/error
    }

    ~Beholder(){
        if(_job.joinable()){

        }
    };

    bool observe(){
        //
        for(;;){
            std::this_thread::sleep_for(std::chrono::seconds(_interval));
            //finger ip + port
            //act if unreachable

            //test msg
            std::cout << "Beholder is watching: " << _ip << " " << _port << std::endl;
        }
        return true;
    };

    std::thread spawn(){
        return std::thread([this](){this->observe();});
    }

    bool stopObservation(){
     //   _job.join();
        return true;
    }
private:
	std::string _ip;
	int _port;
	int _interval;
	std::string _email;
    //std::thread _job;
};

#endif
