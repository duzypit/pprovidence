
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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

class Beholder{
public:
	Beholder(){};
    Beholder(Request r){ add(r); }

    ~Beholder(){
        for(std::thread &t : _threads){
            t.join();
        }
    };

    void observe(Request r){
        try{
            std::cout << "Beholder thread start " << r.ip <<  std::endl;
            boost::asio::io_service io_service;
            std::string tmpPort = std::to_string(r.port);
            boost::asio::ip::tcp::resolver::query query(r.ip, tmpPort.c_str());
            boost::asio::ip::tcp::resolver resolver(io_service);
            boost::asio::ip::tcp::socket socket(io_service);
            boost::system::error_code error;

            std::array<char, 512> buf;
            
            for(;;){
                std::this_thread::sleep_for(std::chrono::seconds(r.interval));
                boost::asio::connect(socket, resolver.resolve(query));
                std::size_t length = boost::asio::read(socket, boost::asio::buffer(buf, 512), boost::asio::transfer_all(), error);
                std::cout << "Beholder is watching: " << r.ip << " " << r.port << " length: " << length << std::endl;

            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }


    void add(Request r){
        _data.push_back(r);
        _threads.push_back(std::thread(&Beholder::observe, this, r));
    }
/*
    bool remove(int id){
        //stub ;)
        std::cout << "Remove Beholder id:" << id << std::endl;
        return true;
    }

    std::string list(){
        //stub ;)
        return std::string("List of Beholder jobs");
    }
*/
private:
    //Beholder worker;
	std::vector<Request> _data;
    std::vector<std::thread> _threads;
};



int main(){
    Request r1 = {std::string("www.google.com"), std::string("tp@gmail.com"), 3, 80};
    std::cout << "Create Master" << std::endl;
    Beholder Master(r1);
    //Request r2 = {std::string("127.0.0.123"), std::string("tp@gmail.com"), 5, 125};
    //Master.add(r2);
    return 0;
}
