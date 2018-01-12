#include "../include/passwd.hpp"
Passwd::Passwd(){}
Passwd::~Passwd(){}

void Passwd::setStdinEcho(bool enable)
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

std::string Passwd::getPassword()
{
    std::string pass;
    setStdinEcho(false);
    std::cin >> pass;
    setStdinEcho();
    return pass;
}
