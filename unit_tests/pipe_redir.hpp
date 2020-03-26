#ifndef __PIPE_TEST_HPP__
#define __PIPE_TEST_HPP__

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


TEST(PipeTest, PipeRedirTest) {

    vector<string> args = {"echo", "\"", "Print", "this", "\"", "|", "cat"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

TEST(PipeRedirTest2, PipeTest2) {

    vector<string> args = {"ls", "|", "grep", ".txt", "|", "grep", "2", "|", "cat"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

#endif //__PIPE_TEST_HPP__
