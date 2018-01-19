#include "../../include/commandParser.hpp"
#include "../../src/commandParser.cpp"
#include <gtest/gtest.h>

class cParserTestHelper : public testing::Test
{
protected:
    CommandParser cparser;

    void testStringTrue(std::string s)
    {
        EXPECT_EQ(cparser.parse(s).valid(), true);
    }

    void testThrow(std:: string s)
    {
        EXPECT_ANY_THROW(cparser.parse(s));
    }
};

TEST_F(cParserTestHelper, valid_string)
{
    testStringTrue("a google.pl 80 10 test@gmail.com");
}

TEST(CommandParser, command_a)
{
    std::string ca1("a google.pl 80 10 test@gmail.com");
    CommandParser cparser;
    cparser.parse(ca1);

    EXPECT_EQ(cparser.valid(), true) << "all args set";

    std::string ca2("a google.pl 80 10");
    EXPECT_ANY_THROW(cparser.parse(ca2));

    std::string ca3("a google.pl 80");
    EXPECT_ANY_THROW(cparser.parse(ca3));

    std::string ca4("a google.pl");
    EXPECT_ANY_THROW(cparser.parse(ca4));

    std::string ca5("a");
    EXPECT_ANY_THROW(cparser.parse(ca5));

    std::string ca6("");
    EXPECT_ANY_THROW(cparser.parse(ca6));

    std::string ca7("a adf");
    EXPECT_ANY_THROW(cparser.parse(ca7));
}


TEST(CommandParser, command_l)
{
    std::string ca1("l");
    CommandParser cparser;
    cparser.parse(ca1);
    EXPECT_EQ(cparser.valid(), true);

    std::string ca2("l 0");
    cparser.parse(ca2);
    EXPECT_EQ(cparser.valid(), true);

    std::string ca3("l 0 khaskdfdhask 4 65 ljlj");
    cparser.parse(ca3);
    EXPECT_EQ(cparser.valid(), true);

    std::string ca4("");
    EXPECT_ANY_THROW(cparser.parse(ca4));

}

TEST(CommandParser, command_s){
    std::string ca1("s 0");
    CommandParser cparser;
    cparser.parse(ca1);
    EXPECT_EQ(cparser.valid(), true);

    std::string ca2("s");
    EXPECT_ANY_THROW(cparser.parse(ca2));

    std::string ca3("");
    EXPECT_ANY_THROW(cparser.parse(ca3));

    std::string ca4("s adfaf");
    EXPECT_ANY_THROW(cparser.parse(ca4));


}

TEST(CommandParser, command_r){

}
