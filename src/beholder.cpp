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
           // std::cout << "Beholder joined!" << std::endl;
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

bool Beholder::lastCheckOk(){
    return _lastCheckOk;
}

std::time_t Beholder::lastCheck(){
    return _lastCheck;
}

bool Beholder::stopped()
{
    return _stop_thread;
}

void Beholder::observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex){
    //gets immediately results on run
    bool alreadyChecked = false;

    while(!_terminate)
    {
        Report event(_r);
        if(alreadyChecked)
        {
            std::unique_lock<std::mutex> beholderLock(_m);
            _cv.wait_for(beholderLock, std::chrono::duration<int>(_r.interval), [&]{ return _terminate; });
        }

        if(!alreadyChecked) alreadyChecked = true;

        if(!_terminate && !_stop_thread)
        {
            ProtocolMinion socket(_r.ip, _r.port);
            event.msg = socket.result();
            event.event_time = std::time(nullptr);
            _lastCheck = event.event_time;
            _lastCheckOk = event.msg.first;
            std::unique_lock<std::mutex> lock(overseerMutex);
            overseerMsgQueue.push_back(event);
        }
    }

}
