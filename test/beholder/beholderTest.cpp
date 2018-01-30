#include "../../include/datatypes.hpp"
#include "../../src/beholder.cpp"
#include "../../src/practicalSocket.cpp"
#include "../../src/protocolMinion.cpp"
#include <gtest/gtest.h>
class BeholderTest : public ::testing::Test
{
protected:
    Request _re;
    std::shared_ptr<Beholder> _b;
    std::mutex _m;
    std::deque<Report> _d;

    virtual void SetUp()
    {
        _re = {"wp.pl", "tp@gmail.com", 1, 80, 0, 'a', false};

        _b = std::make_shared<Beholder>(_re);
    }

    virtual void TearDown(){}
};

TEST_F(BeholderTest, start_stop)
{
    EXPECT_EQ(_b->stopped(), true);
    _b->stop();
    EXPECT_EQ(_b->stopped(), true);
    _b->run();
    EXPECT_EQ(_b->stopped(),false);
}

TEST_F(BeholderTest, thread_start)
{
    _b->run();
    _b->start(_d,_m);
    while (_d.empty())
    {
        //wait for connection establishment, etc.
    }
    bool dequeEmpty = _d.empty();
    EXPECT_EQ(dequeEmpty, false);
    _b->stop();
}

TEST_F(BeholderTest, getters)
{
    EXPECT_EQ(_b->ip(), std::string("wp.pl"));
    EXPECT_EQ(_b->port(), 80);
    EXPECT_EQ(_b->interval(), 1);
    EXPECT_EQ(_b->email(), std::string("tp@gmail.com"));
    EXPECT_EQ(_b->lastCheckOk(), false);

}
