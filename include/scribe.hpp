#ifndef __SCRIBE_HPP__
#define __SCRIBE_HPP__
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <deque>
#include <thread>
#include <condition_variable>
#include <sstream>
#include <iomanip> //std::put_time

#include "../include/datatypes.hpp"
#include "../include/smtpSender.cpp"

class Scribe
{
public:
    Scribe(const std::string& file) : _file(file.c_str(), std::ios::ate) {}

    ~Scribe()
    {
        _stop_thread = true;
        _cv.notify_all();
        if (_thread.joinable())
        {
            _thread.join();
            std::cout << "Scribe joined!" << std::endl;
        }
        _file.close();
    }

    void start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex)
    {
        _stop_thread = false;
        _thread = std::thread(&Scribe::observe, this, std::ref(overseerMsgQueue), std::ref(overseerMutex));
    }

    void stop()
    {
        _stop_thread = true;
    }

    void setUpMailer(GmailCreditenials creditenials){
        _creditenials = creditenials;
    }

private:

    std::ofstream _file;
    std::thread _thread;
    bool _stop_thread;
    std::condition_variable _cv;

    GmailCreditenials _creditenials;

    void save(const Report& e)
    {
        _file << formatMsg(e) << std::endl;
    }

    std::string formatMsg(const Report& e)
    {
        std::string msg;
                std::ostringstream oss;
                std::tm tm = *std::localtime(&e.event_time);
                oss << std::put_time(&tm, "%F %T");
                oss << " ";
                oss << e.ip;
                oss << " ";
                oss << std::to_string(static_cast<int>(e.port));
                oss << " ";
                oss << e.msg.second;
                msg = oss.str();
        return msg;
    }



    void observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex)
    {
        Report e;
        while(!_stop_thread){
           // _cv.wait(lock, [&](){ return (_stop_thread || !overseerMsgQueue.empty()); });
            std::this_thread::sleep_for(std::chrono::seconds(3));

            while(!overseerMsgQueue.empty() && !_stop_thread){
                e = overseerMsgQueue[0];

                std::unique_lock<std::mutex> lock(overseerMutex);
                overseerMsgQueue.pop_front();
                lock.unlock();
                save(e);
                //send email
                if(e.msg.first == true && _creditenials.valid == true)
                {
                    SMTPSender sender;
                    std::string from = _creditenials.uname + "@gmail.com";
                    sender.sendSSL (
                        _creditenials.uname, // userName
                        _creditenials.password, // password
                        from, // from
                        e.email, // to
                        "Testing Boost STMP", // subject
                        "This message body" // message
                    );

                }

            }
        }
    }
};

#endif
