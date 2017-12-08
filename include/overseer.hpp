#ifndef __OVERSEER_HPP__
#define __OVERSEER_HPP__
#include <string>
#include <vector>
#include "beholder.hpp"

class Overseer{
public:
	Overseer();
    ~Overseer();
	bool add(std::string ip, int port, int interval, std::string email);
	bool remove(int id);
	std::string list();

private:
	std::vector<Beholder> _data;
};
#endif
