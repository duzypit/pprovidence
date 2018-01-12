#ifndef __SMTPSENDER_CPP__
#define __SMTPSENDER_CPP__
#include "openSSLBearer.hpp"
#include <iostream>
#include <string>
#include "smtpSocket.hpp"
#include "base64.h"
#include <map>
#include <string>

class SMTPSender
{
public:
    SMTPSender();

    bool verifyCreditenials(const std::string& userName, const std::string& password);

    void sendSSL (const std::string& userName, const std::string& password, const std::string& from, const std::string& to, const std::string& subject, const std::string& message);
private:

    std::string newline;
    std::string _server;    // server address
    int _port;              // server port

    SMTPSocket socket;
    OpenSSLBearer openSSL;

    std::map<int, std::string> _smtpReplyCodes;

    void SMTPReply(const int& code, const std::string msg, bool visible = true);

    void fillReplyCodes();

    bool validReturnMsg(const int& expectedCode, std::string msg);

	static std::string EncodeBase64 (const std::string& data);
};
#endif
