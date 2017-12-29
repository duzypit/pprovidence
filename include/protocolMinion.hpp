#ifndef __PROTOCOL_MINION_HPP__
#define __PROTOCOL_MINION_HPP__
#include <string>

class ProtocolMinion{
public:
    ProtocolMinion();
    virtual ~ProtocolMinion();

private:
    void connect();
    void request();
    void result();

    std::string protocolRequest;

};

class FtpMinion : public ProtocolMinion {

};

class SshMinion : public ProtocolMinion {

};

class SmtpMinion : ProtocolMinion {

};

class Pop3Minion {

};

class HttpMinion : public ProtocolMinion {

};

#endif
