#ifndef __PASSWD_CPP__
#define __PASSWD_CPP__
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>

class Passwd
{
public:
    Passwd();
    ~Passwd();

    void setStdinEcho(bool enable = true);

    std::string getPassword();
};
#endif
