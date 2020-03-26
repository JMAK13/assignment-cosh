#ifndef __TEST_COMMAND_TEST_HPP__
#define __TEST_COMMAND_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"
#include "../src/Container.cpp"


TEST(TestCmdTest, TestCmdTest) {

    vector<Cmd*> cmds;
    vector<string> args = {"[", "-f", "rshell", "]", "&&", "echo", "\"", "path", "exists", "\""};
    vector<string> args2 = {"test", "-d", "header", "&&", "echo", "\"", "path", "exists", "\""};
    vector<string> args3 = {"test", "-d", "asdfasdfa", "||", "echo", "\"", "path", "doesn't", "exist", "\""};
    
    Cmd* c1 = new Container();
    c1->parse(args, false);
    Cmd* c2 = new Container();
    c2->parse(args2, false);
    Cmd* c3 = new Container();
    c3->parse(args3, false);
    
    cmds.push_back(c1);
    cmds.push_back(c2);
    cmds.push_back(c3);

    EXPECT_EQ(cmds[0]->handle(), 0);
    EXPECT_EQ(cmds[1]->handle(), 0);
    EXPECT_EQ(cmds[2]->handle(), 0);
}



#endif //__TEST_COMMAND_TEST_HPP__
