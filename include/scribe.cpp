#ifndef __SCRIBE_HPP__
#define __SCRIBE_HPP__
#include <iostream>
#include <fstream>
#include <string>

class Scribe{
public:
    Scribe(const std::string& file) : _file(file.c_str(), std::ios::ate) {}

    ~Scribe(){
        _file.close();
    }

    void setup(){

    }

    //save smtn to file
    void save(){

    //_file << "data" << std::endl;
    }

private:
    std::ofstream _file;
};

#endif
