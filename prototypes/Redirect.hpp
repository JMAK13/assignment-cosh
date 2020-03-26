#ifndef __REDIRECT_HPP__
#define __REDIRECT_HPP__

#include "../header/cmd.hpp"
#include "../header/Label.hpp"
#include "../src/Pipe.cpp"
#include <stdio.h>     // IO
#include <iostream>    // IO
#include <sys/types.h> // fork() & exec()
#include <unistd.h>    // fork() & exec()
#include <stdlib.h>    // exit() requisit
#include <sys/wait.h>  // waitpid()
#include <errno.h>     // exec() & error()
#include <string.h>
#include <vector>

using namespace std;

class Redirect : public Cmd {
    private:
        vector<Cmd*> tree;
        int status;
    public:
        Redirect();
        virtual int handle();
        virtual int getStatus();
        virtual pid_t getPid();
        virtual string getLabel();
        virtual void addElem(Cmd*);
        virtual Cmd* at(int);
        virtual int size();
        virtual bool parse(vector<string>, bool);
        virtual vector<string> getArgs() { }
};

#endif
