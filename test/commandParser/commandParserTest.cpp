#include "../../include/commandParser.hpp"
#include "../../src/commandParser.cpp"
#include <gtest/gtest.h>

TEST(CommandParser, command_a)
{
    std::string ca1("a google.pl 80 10 test@gmail.com");
    CommandParser cparser;
    cparser.parse(ca1);

    EXPECT_EQ(cparser.valid(), true);

    std::string ca2("a google.pl 80 10");
    cparser.parse(ca2);
    EXPECT_EQ(cparser.valid(), false);

    std::string ca3("a google.pl 80");
    cparser.parse(ca3);
    EXPECT_EQ(cparser.valid(), false);

    std::string ca4("a google.pl");
    cparser.parse(ca4);
    EXPECT_EQ(cparser.valid(), false);

    std::string ca5("a");
    cparser.parse(ca5);
    EXPECT_EQ(cparser.valid(), false);

    std::string ca6("");
    cparser.parse(ca6);
    EXPECT_EQ(cparser.valid(), false);

    std::string ca7("a adf");
    cparser.parse(ca7);
    EXPECT_EQ(cparser.valid(), false);

}

/*
TEST(CommandParser, command_)
{

}
*/
