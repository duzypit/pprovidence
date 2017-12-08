#ifndef __BEHOLDER_HPP__
#define __BEHOLDER_HPP__

#include <string>
#include <thread>

class Beholder{
public:
    Beholder();
	Beholder(std::string ip, int port, int interval, std::string email);
    ~Beholder();
    bool observe();
    bool stopObservation();
private:
	std::string _ip;
	int _port;
	int _interval;
	std::string _email;
    std::thread _job;
};

#endif
