#include <stdio.h>     // IO
#include <iostream>    // IO
#include <sys/types.h> // fork() & exec()
#include <unistd.h>    // fork() & exec()
#include <stdlib.h>    // exit() requisit
#include <sys/types.h> // waitpid()
#include <sys/wait.h>  // waitpid()
#include <errno.h>     // exec() & error()
#include <string.h>
#include <vector>

// Standard namespace
using namespace std;

// User Libraries
#include "base.hpp"

int main(int argc, char* argv[]) {
    cout << "----- Command #1 with arguments -----"<< endl;

    vector<string> cmd1_with_args;
    
    string cmd1 = "echo";
    string cmd1_arg1 = "hello";
    string cmd1_arg2 = "world";
    
    cmd1_with_args.push_back(cmd1);
    cmd1_with_args.push_back(cmd1_arg1);
    cmd1_with_args.push_back(cmd1_arg2);
    
    Base *Command1 = new Base(cmd1_with_args);
    Command1->execCmd();
    
    cout << endl;
    
    // If we want to use && we would check for it as a string and make another class
    
    cout << "----- Command #2 with arguments -----"<< endl;
    
    vector<string> cmd2_with_args;
   
    string cmd2 = "ls";
    string cmd2_arg1 = "-a";
    
    cmd2_with_args.push_back(cmd2);
    cmd2_with_args.push_back(cmd2_arg1);

    Base *Command2 = new Base(cmd2_with_args);
    Command2->execCmd();
    
    cout << endl;
    
    
    // Exit Program
    return 0;
}
