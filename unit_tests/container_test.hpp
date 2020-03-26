#ifndef __CONTAINER_TEST_HPP__
#define __CONTAINER_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"
#include "../src/Container.cpp"


TEST(ContainerTest, ContainerTest) {

    vector<Cmd*> cmds;
    vector<string> args = {"(", "echo", "1", "&&", "echo", "2", ";", ")", "&&", "(", "fail", ")", "||", "echo", "success"};
    
    Cmd* c1 = new Container();
    c1->parse(args, false);
    
    cmds.push_back(c1);

    EXPECT_EQ(cmds[0]->handle(), 0);
}



#endif //__CONTAINER_TEST_HPP__
