#include "../../src/protocolMinion.cpp"
#include "../../src/practicalSocket.cpp"
#include <gtest/gtest.h>
#include <memory>

class protocolMinionTest : public ::testing::Test
{
    protected:
        std::shared_ptr<ProtocolMinion> _p;

        virtual void SetUp()
        {
            _p = std::make_shared<ProtocolMinion>(std::string("wp.pl"), 80);
        }

        virtual void TearDown()
        {

        }

};

TEST_F(protocolMinionTest, test1)
{
    //std::cout << _p -> result().first << ", " << _p -> result().second << std::endl;
    EXPECT_EQ(_p->result().first, false);
    bool found = _p->result().second.find(std::string("OK"));
    EXPECT_EQ(found, true);
}

