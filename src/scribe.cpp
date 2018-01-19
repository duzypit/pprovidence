#include "../include/scribe.hpp"

Scribe::Scribe() : _file(std::string("pprovidence.log").c_str(), std::ios::app) {}

Scribe::~Scribe()
{
    _stop_thread = true;
    _cv.notify_all();
    if (_thread.joinable())
    {
        _thread.join();
        //std::cout << "Scribe joined!" << std::endl;
    }
    _file.close();
}

void Scribe::start(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex)
{
    _stop_thread = false;
    _thread = std::thread(&Scribe::observe, this, std::ref(overseerMsgQueue), std::ref(overseerMutex));
}

void Scribe::stop()
{
    _stop_thread = true;
}

void Scribe::setUpMailer(GmailCreditenials creditenials){
    _creditenials = creditenials;
}

void Scribe::save(const Report& e)
{
    _file << formatMsg(e) << std::endl;
}

std::string Scribe::formatMsg(const Report& e)
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



void Scribe::observe(std::deque<Report>& overseerMsgQueue, std::mutex& overseerMutex)
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
                std::string subject = "PProvidence: host " + e.ip + " unreachable";
                sender.sendSSL (
                    _creditenials.uname, // userName
                    _creditenials.password, // password
                    from, // from
                    e.email, // to
                    subject, // subject
                    formatMsg(e) // message
                );

            }

        }
    }
}
