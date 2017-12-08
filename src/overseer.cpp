#include "../include/overseer.hpp"

Overseer::Overseer() : _data(10){

}

Overseer::~Overseer(){

}

bool Overseer::add(std::string ip, int port, int interval, std::string email){
    Beholder Servant(ip, port, interval, email);
    _data.push_back(Servant.observe());
    return true;
}
bool Overseer::remove(int id){
    //stub ;)
    return true;
}
std::string Overseer::list(){
    //stub ;)
    return std::string("List of overseer jobs");
}
