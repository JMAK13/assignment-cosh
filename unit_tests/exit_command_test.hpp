#ifndef __EXIT_COMMAND_TEST_HPP__
#define __EXIT_COMMAND_TEST_HPP__

#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"
#include "../src/Container.cpp"


TEST(ExitCmdTest, ExitCmdTest) {

    vector<Cmd*> cmds;
    vector<string> args = {"(", "echo", "1", "&&", "exit", "2", ";", ")", "&&", "(", "ls", ")"};
    
    Cmd* c1 = new Container();
    c1->parse(args, false);
    
    cmds.push_back(c1);

    EXPECT_EQ(cmds[0]->handle(), 1);
}



#endif //__EXIT_COMMAND_TEST_HPP__
