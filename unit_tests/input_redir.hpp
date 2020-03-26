#ifndef __INPUT_REDIR_TEST_HPP__
#define __INPUT_REDIR_TEST_HPP__

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


TEST(InputRedirTest, InputRedirTest) {

    vector<string> args = {"cat", "<", "test.txt"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

TEST(InputRedirTest2, InputRedirTest2) {

    vector<string> args = {"echo", "testing", ">", "test.txt", "&&", "cat", "<", "test.txt"};
    
    Cmd* c1 = new Redirect();
    c1->parse(args, false);

    EXPECT_EQ(c1->handle(), 0);
}

#endif //__INPUT_REDIR_TEST_HPP__
