#include "../include/commandParser.hpp"
CommandParser::CommandParser(){}

CommandParser& CommandParser::parse(const std::string& source, bool addToCfgFile)
{
    std::vector<std::string> splittedSource = split(source, ' ');
    _data.valid = false;
    if(!source.empty())
    {
        _data.command = splittedSource[0][0];
        _data.valid = true;
        if(_data.command == 'a')
        {
            if(splittedSource.size() == 5)
            {
                _data.ip = splittedSource[1];
                _data.email = splittedSource[4];
                _data.interval = atoi(splittedSource[3].c_str());
                _data.port = atoi(splittedSource[2].c_str());
            } else
            {
                _data.valid = false;
                std::cout << "commandParser: too few args for add command. Aborted." << std::endl;
            }


        } else if(_data.command == 's')
        {
            if(splittedSource.size() >= 2)
            {
                try{
                    _data.job_id = std::stoi(splittedSource[1].c_str());
                } catch(const std::invalid_argument& e){
                    _data.valid = false;
                    std::cout << "commandParser(" << e.what() << "): invalid argument. Aborted."<< std::endl;
                }

            } else
            {
                _data.valid = false;
                std::cout << "commandParser: too few args for stop command. Aborted." << std::endl;
            }
        } else if(_data.command == 'r')
        {
            if(splittedSource.size() >= 1)
            {
                 try{
                    _data.job_id = std::stoi(splittedSource[1].c_str());
                } catch(const std::invalid_argument& e){
                    _data.valid = false;
                    std::cout << "commandParser(" << e.what() << "): invalid argument. Aborted."<< std::endl;
                }

               //_data.job_id = atoi(splittedSource[1].c_str());
            } else
            {
                _data.valid = false;
                std::cout << "commandParser: too few args for run command. Aborted." << std::endl;
            }

        }

        if (addToCfgFile == true && _data.valid == true && _data.command == 'a'){
            //save command to config file
            std::ofstream cfg("pprovidence.cfg", std::ios::app);
            cfg << source << std::endl;
            cfg.close();
        }
    }
    return *this;
}

std::vector<std::string> CommandParser::split(const std::string& source, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(source);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

//debug
CommandParser& CommandParser::print() noexcept
{
    std::cout << std::endl;
    std::cout << "commandParser data: " << std::endl;
    std::cout << "command: " << _data.command << std::endl;
    if(_data.command == 'a')
    {
        std::cout << "ip: " << _data.ip << std::endl;
        //std::cout << "port: " << _data.port << std::endl;
        std::cout << "port: " << static_cast<int>(_data.port) <<std::endl;
        std::cout << "interval (s): " << _data.interval << std::endl;
        std::cout << "email: " << _data.email << std::endl;
    }
    if(_data.command == 'd')
    {
        std::cout << "job_id: " << _data.job_id << std::endl;
    }
    std::cout << std::endl;

    return *this;
}

Request CommandParser::req_struct() const noexcept
{
    return _data;
}

bool CommandParser::valid() const noexcept
{
    return _data.valid;
}

