#include "../include/commandLoader.hpp"
CommandLoader::CommandLoader(const std::string& filename)
{
    dispatchFile(filename);
}

CommandLoader::~CommandLoader(){}

std::vector<std::string> CommandLoader::requestsVector()
{
    return _reqVec;
}

void CommandLoader::dispatchFile(const std::string& filename)
{
    std::fstream ifs(filename);
    if (ifs.is_open())
    {
        std::string line;
        while(std::getline(ifs, line))
        {
            _reqVec.push_back(line);
        }
    }
    else
    {
        std::cout << "Couldn't open " << filename << " for reading" << std::endl;
    }
}
