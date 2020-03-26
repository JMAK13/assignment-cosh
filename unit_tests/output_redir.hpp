#ifndef __OUPUT_REDIR_TEST_HPP__
#define __OUPUT_REDIR_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"
#include "../src/Container.cpp"
#include "../src/Redirect.cpp"


TEST(OutputRedirTest, OutputRedirTest) {

    vector<string> args = {"ls", ">", "test.txt"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

TEST(OutputRedirTest2, OutputRedirTest2) {

    vector<string> args = {"echo", "testing", ">", "test2.txt", ">", "test3.txt", ">", "test.txt"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

#endif //__OUPUT_REDIR_TEST_HPP__
