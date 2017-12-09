
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>

class Beholder{
private:
    std::thread _job;
	std::string _ip;
	int _port;
	int _interval;
	std::string _email;

public:
    Beholder(std::string ip, int port, int interval, std::string email) : _job(), _ip(ip), _port(port), _interval(interval), _email(email) {

        //setup
        //create protocol minion
        //start observation
        //signal success/error
        this->spawn();
    }

    ~Beholder(){
        if(_job.joinable()) _job.join();
    };

    bool observe(){
        std::cout << "Beholder thread start" << std::endl;
        for(;;){
            std::this_thread::sleep_for(std::chrono::seconds(_interval));
            std::cout << "Beholder is watching: " << _ip << " " << _port << std::endl;

        }
        return true;
    }

    void spawn(){
        this->_job =  std::thread(&Beholder::observe,this);
    }

    bool stop(){
        _job.join();
        return true;
    }
};

class Overseer{
public:
	Overseer(){};

    ~Overseer(){};

    bool add(std::string ip, int port, int interval, std::string email){
        Beholder servant(ip, port, interval, email);
        _data.push_back(servant);
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



int main(){
    std::cout << "Create Master" << std::endl;
    Overseer Master;
    Master.add(std::string("127.0.0.1"), 80, 3, std::string("tp@gmail.com"));
    return 0;
}
