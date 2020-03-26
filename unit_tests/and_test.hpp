#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"


TEST(AndTest, AndTest) {

    vector<Cmd*> cmds;
    vector<string> args;
    vector<string> args2;
    
    string cmd1 = "echo";
    string cmd1_arg1 = "command";
    string cmd1_arg2 = "one";
    
    string cmd2 = "echo";
    string cmd2_arg1 = "command";
    string cmd2_arg2 = "two";
    
    args.push_back(cmd1);
    args.push_back(cmd1_arg1);
    args.push_back(cmd1_arg2);
    
    args2.push_back(cmd2);
    args2.push_back(cmd2_arg1);
    args2.push_back(cmd2_arg2);
    
    Cmd* c1 = new Label(args);
    Cmd* c2 = new Label(args2);
    Cmd* c3 = new And(c1, c2);
    
    cmds.push_back(c1);
    cmds.push_back(c3);

    EXPECT_EQ(cmds[0]->handle(), 0);
    EXPECT_EQ(cmds[1]->handle(), 0);
}



#endif //__AND_TEST_HPP__
