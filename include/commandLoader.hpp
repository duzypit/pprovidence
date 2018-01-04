#ifndef __COMMAND_LOADER_HPP__
#define __COMMAND_LOADER_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <iterator>
#include <iostream>


class CommandLoader{
public:
    CommandLoader(const std::string& filename){
        dispatchFile(filename);
    }

    ~CommandLoader(){}

    std::vector<std::string> requestsVector(){
        return _reqVec;
    }
private:
    void dispatchFile(const std::string& filename){
        std::fstream ifs(filename);
        if (ifs) {
            std::string line;
            while(std::getline(ifs, line)){
                _reqVec.push_back(line);
            }
        }
        else {
            std::cout << "Couldn't open " << filename << " for reading" << std::endl;
        }


    }
    std::vector<std::string> _reqVec;
};


#endif

