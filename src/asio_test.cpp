#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <boost/asio.hpp>


struct Request{
	std::string ip;
	std::string port;
};

int main(){
		Request r {"www.google.pl", "80"};
        try{
            std::cout << "Beholder thread start " << r.ip <<  std::endl;
            boost::asio::io_service io_service;
            //std::string tmpPort = std::to_string(r.port);
            boost::asio::ip::tcp::resolver::query query(r.ip, r.port);
            boost::asio::ip::tcp::resolver resolver(io_service);
            boost::asio::ip::tcp::socket socket(io_service);
            boost::system::error_code error;

            std::vector<char> buf(512);
            
            //for(;;){
                //std::this_thread::sleep_for(std::chrono::seconds(r.interval));
                boost::asio::connect(socket, resolver.resolve(query));
                std::cout << "connect" << std::endl;
                //std::size_t length = boost::asio::read(socket, boost::asio::buffer(buf, 512), boost::asio::transfer_all(), error);
                
                std::size_t length = socket.read_some(boost::asio::buffer(buf, 512), error);
                std::cout << "read" << std::endl;
                std::cout << "Beholder is watching: " << r.ip << " " << r.port << " length: " << length << std::endl;

            //}
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

    std::cout << "bye" << std::endl;
    return 0;
}