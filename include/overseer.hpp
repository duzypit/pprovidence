#ifndef __OVERSEER_HPP__
#define __OVERSEER_HPP__
#include <thread>
#include <vector>
#include <algorithm>

#include "../include/datatypes.hpp"
#include "../include/beholder.cpp"

class Overseer{
public:
	Overseer(){};
    Overseer(Request r){ add(r); }

    ~Overseer(){};

    void dispatch(const Request& r){
        switch (r.command) {
            case 'a':
                add(r);
                break;
            case 'l':
                list_jobs();
                break;
            case 'd':

                break;

            default:
                std::cout << "Overseer: Unknown command! Aborted." << std::endl;
        }
    }

    void add(const Request& r){
        auto tmp = std::make_shared<Beholder>(r);
        tmp -> start();
        _threads.push_back(tmp);
    }

    void remove(std::size_t id){
        if(_threads[id] -> stopped() == false)
            _threads[id] -> stop();
    }

    void list_jobs(){
        if(_threads.size() != 0) {
            std::cout << "id " << "ip " << "port " << "interval " << "email " << "sleeping/working" << std::endl;
            for(auto& b : _threads ){
                std::cout << std::distance(_threads.begin(), std::find(_threads.begin(), _threads.end(), b)) << " "
                    << b->ip() << " "
                    << b->port() << " "
                    << b->interval() << " "
                    << b->email() << " "
                    << (b->stopped() ? "sleeping" : "working") << " "
                    << std::endl;
            }
        } else {
            std::cout << "Overseer: no jobs to list." << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<Beholder>> _threads;
};

#endif
