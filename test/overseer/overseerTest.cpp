#include "../../src/overseer.cpp"
#include "../../src/scribe.cpp"
#include "../../src/beholder.cpp"
#include "../../src/smtpSender.cpp"
#include "../../src/protocolMinion.cpp"
#include "../../src/openSSLBearer.cpp"
#include <gtest/gtest.h>


class OverseerTestHelper : public testing::Test {
    protected:
        Overseer master;

        void addCommand(Request& r){
            master.dispatch(r);
        }
};

TEST(Overseer, unknown_command){
    Request r;
    r.command = 'x'; //unknown command

    Overseer master;
    EXPECT_ANY_THROW(master.dispatch(r));

}
