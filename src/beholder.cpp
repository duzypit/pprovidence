#include "../include/beholder.hpp"
Beholder::Beholder(){};

Beholder::Beholder(std::string ip, int port, int interval, std::string email) : _ip(ip), _port(port), _interval(interval), _email(email){

}

Beholder::~Beholder(){

}

bool Beholder::observe(){

}
