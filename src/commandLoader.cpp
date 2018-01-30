#include "../include/commandLoader.hpp"
CommandLoader::CommandLoader(const std::string& filename)
{
        dispatchFile(filename);
}

CommandLoader::CommandLoader(const std::string& filename, const std::string& command)
{
    save(filename, command);
}

void CommandLoader::save(const std::string& filename, const std::string& command)
{
    std::ofstream cfg(filename, std::ios::app);
    cfg << command << std::endl;
    cfg.close();
}

CommandLoader::~CommandLoader(){}

std::vector<std::string> CommandLoader::requestsVector()
{
    return _reqVec;
}

void CommandLoader::dispatchFile(const std::string& filename)
{
    std::fstream cfg(filename);
    if (cfg.is_open())
    {
        std::string line;
        while(std::getline(cfg, line))
        {
            _reqVec.push_back(line);
        }
    }
    else
    {
        std::cout << "Couldn't open " << filename << " for reading" << std::endl;
    }
}
