#ifndef __COMMAND_PARSER_HPP__
#define __COMMAND_PARSER_HPP__
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "../include/datatypes.hpp"

class CommandParser
{
public:

    CommandParser();

    CommandParser& parse(const std::string& source);

    std::vector<std::string> split(const std::string& source, char delim);

    //debug
    CommandParser& print() noexcept;

    Request req_struct() const noexcept;

    bool valid() const noexcept;

private:
    Request _data;
};
#endif
