#ifndef __COMMAND_LOADER_HPP__
#define __COMMAND_LOADER_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <iterator>
#include <iostream>

class CommandLoader
{
public:
    CommandLoader(const std::string& filename);
    CommandLoader(const std::string& filename, const std::string& command);

    ~CommandLoader();

    std::vector<std::string> requestsVector();

private:
    void save(const std::string& filename, const std::string& command);

    std::vector<std::string> _reqVec;
    void dispatchFile(const std::string& filename);

};
#endif

