#include "../include/beholder.hpp"

Beholder::Beholder(Request r) : _thread(), _stop_thread(true), _r(r) {}

Beholder::~Beholder()
    {
        _terminate = true;
        _stop_thread = true;
        _cv.notify_all();

        if(_thread.joinable())
        {
            _thread.join();
            std::cout << "Beholder joined!" << std::endl;
        }
    }

void Beholder::start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex)
{
    _stop_thread = false;
    _thread = std::thread(&Beholder::observe, this, std::ref(overseerMsgQueue), std::ref(overseerMutex));
}

void Beholder::stop()
{
    _stop_thread = true;
}

void Beholder::run()
{
    _stop_thread = false;
    std::unique_lock<std::mutex> beholderLock(_m);
    beholderLock.unlock();
}

std::string Beholder::ip()
{
    return _r.ip;
}

int Beholder::port()
{
    return static_cast<int>(_r.port);
}

int Beholder::interval()
{
    return _r.interval;
}

std::string Beholder::email()
{
    return _r.email;
}

bool Beholder::stopped()
{
    return _stop_thread;
}

void Beholder::observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex){
    while(!_terminate)
    {
        Report error(_r);
        std::unique_lock<std::mutex> beholderLock(_m);
        _cv.wait_for(beholderLock, std::chrono::duration<int>(_r.interval), [&]{ return _terminate; });
        if(!_terminate && !_stop_thread)
        {
            ProtocolMinion socket(_r.ip, _r.port);
            error.msg = socket.result();
            error.event_time = std::time(nullptr);
            std::unique_lock<std::mutex> lock(overseerMutex);
            overseerMsgQueue.push_back(error);
        }
    }
/*
    while(!_terminate)
    {
        Report error(_r);
        std::unique_lock<std::mutex> beholderLock(_m);
        _cv.wait_for(beholderLock, std::chrono::duration<int>(_r.interval), [&]{ return !_stop_thread; });
        if(!_terminate && !_stop_thread)
        {
            ProtocolMinion socket(_r.ip, _r.port);
            error.msg = socket.result();
            error.event_time = std::time(nullptr);
            std::unique_lock<std::mutex> lock(overseerMutex);
            overseerMsgQueue.push_back(error);
        }
    }
*/
}
