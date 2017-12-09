#ifndef __OVERSEER_HPP__
#define __OVERSEER_HPP__

#include <string>
#include <vector>
#include "beholder.cpp"

class Overseer{
public:
	Overseer();

    ~Overseer();

    bool add(std::string ip, int port, int interval, std::string email){
        Beholder Servant(ip, port, interval, email);
        _data.push_back(Servant);
        return true;
    }

    bool remove(int id){
        //stub ;)
        std::cout << "Remove Beholder id:" << id << std::endl;
        return true;
    }

    std::string list(){
        //stub ;)
        return std::string("List of overseer jobs");
    }
private:
	std::vector<Beholder> _data;
};

#endif
