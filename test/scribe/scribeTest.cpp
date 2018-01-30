#include "../../src/scribe.cpp"
#include "../../src/smtpSocket.cpp"
#include "../../src/smtpSender.cpp"
#include "../../src/openSSLBearer.cpp"
#include "../../src/practicalSocket.cpp"
#include <gtest/gtest.h>
#include <cstdio> //std::remove

TEST(Scribe, write_to_file){
    std::deque<Report> d;

    Report r;
    r.ip = "wp.pl";
    r.email = "test@test.pl";
    r.interval = 5;
    r.port = 80;
    r.job_id = 0;
    r.msg.first = false;
    r.msg.second = "OK!";
    r.event_time = 0;
    d.push_back(r);

    {
        Scribe s;
        std::mutex m;
        s.start(d, m);
        while(!d.empty())
        {
            //wait till scribe thread empty deque
        }
        //scribe wil be destroyed in three.. two...
    }

    //load file
    std::ifstream ifs("pprovidence.log");
    std::string line;
    std::getline(ifs, line);
	EXPECT_STREQ(line.c_str(), "1970-01-01 01:00:00 wp.pl 80 OK!");

//remove log file
    std::remove("pprovidence.log");

}
