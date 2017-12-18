
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>

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
    int job_id;
    char command;
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
public:
    commandParser(){}

    commandParser& parse(const std::string& source){
        std::vector<std::string> splittedSource = split(source, ' ');

        _data.command = splittedSource[0][0];
        if(_data.command == 'a'){
            _data.ip = splittedSource[1];
            _data.email = splittedSource[4];
            _data.interval = atoi(splittedSource[3].c_str());
            _data.port = 2;


        } else if(_data.command == 'd'){
            _data.job_id = atoi(splittedSource[1].c_str());

        }

        return *this;
    }

    std::vector<std::string> split(const std::string& source, char delim){
        std::vector<std::string> result;
        std::stringstream ss(source);
        std::string item;
        while(std::getline(ss, item, delim)){
            result.push_back(item);
        }

        return result;
    }

    //debug
    commandParser& print(){
        std::cout << std::endl;
        std::cout << "commandParser data: " << std::endl;
        std::cout << "command: " << _data.command << std::endl;
        if(_data.command == 'a'){
            std::cout << "ip: " << _data.ip << std::endl;
            std::cout << "port: " << _data.port << std::endl;
            std::cout << "interval (s): " << _data.interval << std::endl;
            std::cout << "email: " << _data.email << std::endl;
        }
        if(_data.command == 'd'){
            std::cout << "job_id: " << _data.job_id << std::endl;
        }
        std::cout << std::endl;

        return *this;
    }

    void clear();

private:
    Request _data;
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
    std::cout << "Type a command (q - quit, ? - help)." << std::endl;
    commandParser cparser;
    for(;;){
        std::cout << ">:";
        command.clear();

        std::getline(std::cin, command);
        if(command == "?"){
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "\ta ip port interval(seconds) email - add a service to watch " << std::endl;
            std::cout << "\tl - list all current jobs with id's" << std::endl;
            std::cout << "\td job_id - delete job" <<std::endl;
            std::cout << std::endl;
        } else if(command == "q") {
            break;
        } else {
            cparser.parse(command).print();
        }

    }
    return 0;
}
