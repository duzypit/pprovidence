#include "../include/commandIOMinion.hpp"
CommandIOMinion::CommandIOMinion(const std::string& filename)
{
        dispatchFile(filename);
}

CommandIOMinion::CommandIOMinion(const std::string& filename, const std::string& command)
{
    save(filename, command);
}

void CommandIOMinion::save(const std::string& filename, const std::string& command)
{
    std::ofstream cfg(filename, std::ios::app);
    cfg << command << std::endl;
    cfg.close();
}

CommandIOMinion::~CommandIOMinion(){}

std::vector<std::string> CommandIOMinion::requestsVector()
{
    return _reqVec;
}

void CommandIOMinion::dispatchFile(const std::string& filename)
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
