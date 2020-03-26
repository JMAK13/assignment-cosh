#ifndef __SINGLE_COMMAND_TEST_HPP__
#define __SINGLE_COMMAND_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"


TEST(SingleCommandTest, EchoTest) {

    vector<Cmd*> cmds;
    vector<string> args;
    
    string cmd1 = "echo";
    string cmd1_arg1 = "hello";
    string cmd1_arg2 = "&&";
    string cmd1_arg3 = "world";
    
    args.push_back(cmd1);
    args.push_back(cmd1_arg1);
    args.push_back(cmd1_arg2);
    args.push_back(cmd1_arg3);
    
    Cmd* c1 = new Label(args);
    cmds.push_back(c1);

    EXPECT_EQ(cmds[0]->handle(), 0);
}

TEST(SingleCommandTest, lsTest) {

    vector<Cmd*> cmds;
    vector<string> args;
    
    string cmd1 = "ls";
    string cmd1_arg1 = "-a";

    args.push_back(cmd1);
    args.push_back(cmd1_arg1);

    Cmd* c1 = new Label(args);
    cmds.push_back(c1);

    EXPECT_EQ(cmds[0]->handle(), 0);
}



#endif //__SINGLE_COMMAND_TEST_HPP__
