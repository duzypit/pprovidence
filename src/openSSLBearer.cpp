#include "../lib/openSSLBearer.hpp"
OpenSSLBearer::OpenSSLBearer(int socket, const SSL_METHOD *method) : ctx_ (nullptr, SSL_CTX_free), ssl_ (nullptr, SSL_free)
{
    initialize();
    char errorBuf[errorBufSize];
    // Then an SSL CTX object is created as a framwork to establish TLS/SSL enabled connections.
    ctx_ = decltype(ctx_) (SSL_CTX_new(method), SSL_CTX_free);
    if (ctx_ == nullptr) throw std::runtime_error (ERR_error_string(ERR_get_error(), errorBuf));
    //Create SSL struct that hold data for the connection.ssl = declitype
    ssl_ = decltype(ssl_)(SSL_new(ctx_.get()), SSL_free);
    if (ssl_ == nullptr) throw std::runtime_error (ERR_error_string(ERR_get_error(), errorBuf));
    // When a network connection has been created, it can be assigned to an SSL object.
    // After the SSL object has been created using SSL new,
    // SSL set fd or SSL set bio can be used to associate the network connection with the object.

    const int rstSetFd = SSL_set_fd(ssl_.get(), socket);
    if (rstSetFd == 0) throw std::runtime_error (ERR_error_string(ERR_get_error(), errorBuf));


    // Then TLS/SSL handshake is performed using SSL accept or SSL connect respectively.
    const int rstConnect = SSL_connect(ssl_.get());
    if (rstConnect == 0)
    {
        throw std::runtime_error (ERR_error_string(ERR_get_error(), errorBuf));
    }
    else if (rstConnect < 0)
    {
        throw std::runtime_error ("OpenSSLBearer: handshake and shutdown failed.");
    }
}

void OpenSSLBearer::write(const std::string& msg)
{
    const int rstWrite = SSL_write(ssl_.get(), msg.c_str(), msg.length());
    if (rstWrite == 0)
    {
        throw std::runtime_error("OpenSSLBearer: socket write failed due to lose connection.");
    }
    else if ( rstWrite < 0)
    {
        throw std::runtime_error ("OpenSSLBearer: socket write failed due to unknown reason.");
    }
}


std::string OpenSSLBearer::read()
{
    char buf[readBufSize];
    std::string read;
    bool waitForRead;
    while (true)
    {
        waitForRead = false;
        const int rstRead = SSL_read (ssl_.get(), buf, readBufSize);
        if (rstRead == 0)
        {
            throw std::runtime_error("OpenSSLBearer: Connection lost while read.");
        }

        //wait for the socket to be readable, then call this fucn again
        if (rstRead < 0 && SSL_ERROR_WANT_READ == SSL_get_error(ssl_.get(), rstRead))
        {
            waitForRead = true;
            continue;
        }

        read += std::string(buf, buf + rstRead);
        if (!waitForRead) return read;
    }
}

OpenSSLBearer::~OpenSSLBearer()
{
    SSL_shutdown(ssl_.get());
    FIPS_mode_set(0);

    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

}

void OpenSSLBearer::initialize()
{
    ERR_load_crypto_strings();
    SSL_load_error_strings();
    SSL_library_init();
}


