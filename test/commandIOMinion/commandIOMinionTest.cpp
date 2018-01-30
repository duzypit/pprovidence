#include "../../src/commandIOMinion.cpp"
#include <gtest/gtest.h>
#include <cstdio>
#include <vector>
#include <string>
class cIOMinionTestHelper : public testing::Test
{
protected:

    void SetUp()
    {
        std::ofstream ofs;
        ofs.open("test.txt");
        ofs << "success" << std::endl;
        ofs.close();
    }

    void TearDown()
    {
        std::remove("test.txt");
    }

    void testFile()
    {
        CommandIOMinion cLoader("test.txt");
        std::vector<std::string> result = cLoader.requestsVector();
        EXPECT_EQ(result[0], std::string("success"));
    }
};

TEST(commandIOMinion, no_file_created)
{
    testing::internal::CaptureStdout();
    CommandIOMinion cLoader("anothertest.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string("Couldn't open anothertest.txt for reading\n"));
}

TEST_F(cIOMinionTestHelper, succesfulRead)
{
    testFile();
}
