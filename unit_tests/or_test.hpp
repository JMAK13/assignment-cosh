#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"


TEST(OrTest, OrTest) {

    vector<Cmd*> cmds;
    vector<string> args;
    vector<string> args2;
    
    string cmd1 = "fail";
    
    string cmd2 = "echo";
    string cmd2_arg1 = "first";
    string cmd2_arg2 = "failed";
    
    args.push_back(cmd1);
    
    args2.push_back(cmd2);
    args2.push_back(cmd2_arg1);
    args2.push_back(cmd2_arg2);
    
    Cmd* c1 = new Label(args);
    Cmd* c2 = new Label(args2);
    Cmd* c3 = new Or(c1, c2);
    
    cmds.push_back(c1);
    cmds.push_back(c3);

    EXPECT_EQ(cmds[0]->handle(), -1);
    EXPECT_EQ(cmds[1]->handle(), 0);
}



#endif //__OR_TEST_HPP__
