//#include "../../include/commandParser.hpp"
#include "../../src/commandParser.cpp"
#include "../../src/commandIOMinion.cpp"
#include <gtest/gtest.h>

class cParserTestHelper : public testing::Test
{
protected:
    CommandParser cparser;

    void testStringTrue(std::string s)
    {
        EXPECT_EQ(cparser.parse(s).valid(), true);
    }

    void testThrow(std:: string s, std::string msg = "testThrow")
    {
        EXPECT_ANY_THROW(cparser.parse(s)) << msg;
    }
};

TEST_F(cParserTestHelper, a_command)
{
    testStringTrue("a google.pl 80 10 test@gmail.com");
    testThrow("a google.pl 80 10", "one arg missing");
    testThrow("a google.pl 80", "two args missing");
    testThrow("a google.pl", "three args missing");
    testThrow("a", "command only");
    testThrow("", "empty string");
    testThrow("a adf", "command a & random chars");

}


TEST_F(cParserTestHelper, l_command)
{
    testStringTrue("l");
    //all things after command will be sliced by dispatcher
    testStringTrue("l 0");
    testStringTrue("l khaskdfdhask 4 65 ljlj");
    testThrow("", "empty string");

}

TEST_F(cParserTestHelper, s_command){
    testStringTrue("s 0");
    testThrow("s");
    testThrow("");
    testThrow("s adfaf");
}

TEST_F(cParserTestHelper, r_command){
    testStringTrue(" 0");
    testThrow("r");
    testThrow("");
    testThrow("r adfaf");

}

TEST_F(cParserTestHelper, d_command){
    testStringTrue("d 0");
    testThrow("d");
    testThrow("");
    testThrow("d adfaf");

}

TEST_F(cParserTestHelper, c_command){
    testStringTrue("c");
    testThrow("");
    //all things after command will be sliced by dispatcher
    testStringTrue("c adfaf");
}

TEST_F(cParserTestHelper, q_command){
    //all things after command will be sliced by dispatcher
    testStringTrue("q 0");
    testThrow("");
    testStringTrue("q adfaf");
}

TEST_F(cParserTestHelper, question_mark_command){
    //all things after command will be sliced by dispatcher
    testStringTrue("? 0");
    testThrow("");
    testStringTrue("? adfaf");

}
