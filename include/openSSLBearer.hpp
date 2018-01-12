#ifndef __MYOPENSSL_CPP__
#define __MYOPENSSL_CPP__

//first sudo apt-get install libssl-dev
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <memory>
#include <iostream>


class OpenSSLBearer
{
public:
    // method can be one of SSLv2 method, SSLv3 method, TLSvl method or SSLv23 method.
    OpenSSLBearer(int socket, const SSL_METHOD *method = SSLv23_method());

    void write(const std::string& msg);

    std::string read();

    ~OpenSSLBearer();

private:
    void initialize();

    std::unique_ptr<SSL_CTX, decltype (SSL_CTX_free)*> ctx_;
    std::unique_ptr<SSL, decltype (SSL_free)*> ssl_;
    enum
    {
        errorBufSize = 256,
        readBufSize = 256
    };	// may need to increase these sizes.
};
#endif
