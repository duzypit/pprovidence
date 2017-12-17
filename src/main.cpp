
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>


enum class Protocol {
    ftp=20,
    ssh = 22,
    smtp=25,
    http = 80,
    pop3=110
};

struct Request{
    std::string ip;
    std::string email;
    int interval;
    int port;
};

class protocolMinion{
    public:
    protocolMinion(Request r) : _thread(), _stop_thread(false), _r(r) {}
    ~protocolMinion(){
        _stop_thread = true;
        if(_thread.joinable()) _thread.join();
    }

    protocolMinion(const protocolMinion&) = delete;
    protocolMinion(protocolMinion &&) = delete;

    void start(){
        _thread = std::thread(&protocolMinion::observe, this);
    }

    private:
        std::thread _thread;
        bool _stop_thread;
        Request _r;
        void observe(){
            while(!_stop_thread){
                std::this_thread::sleep_for(std::chrono::seconds(_r.interval));
                std::cout << "protocolMinion is watching: " << _r.ip << " " << _r.port << std::endl;


            }
        }
};

class Beholder{
public:
	Beholder(){};
    Beholder(Request r){ add(r); }

    ~Beholder(){};

    void add(Request r){
        auto tmp = std::make_shared<protocolMinion>(r);
        tmp -> start();
        _threads.push_back(tmp);
    }

    bool remove(int id);

    std::string list();

private:
    //Beholder worker;
    std::vector<std::shared_ptr<protocolMinion>> _threads;
};

class commandParser{
    commandParser(){}

    void parse();

    void clear();
};

int main(){
    //google
    //Request r1 = {std::string("172.217.16.3"), std::string("tp@gmail.com"), 3, 80};
    //std::cout << "Create Master" << std::endl;
    //Beholder Master(r1);
    //Request r2 = {std::string("127.0.0.123"), std::string("tp@gmail.com"), 5, 125};
    //Master.add(r2);
    std::string command;

    std::cout << std::string(80, '\n');
    for(;;){
        command.clear();
        std::cout << "Type a command (q - quit, ? - help)." << std::endl;
        std::cin >> command;
        if(command == "?"){
        std::cout << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "add ip port interval(seconds) email" << std::endl;
        std::cout << "list" << std::endl;
        std::cout << "delete job_id" <<std::endl;
        std::cout << std::endl;
        } else if(command == "q") break;

    }
    return 0;
}
