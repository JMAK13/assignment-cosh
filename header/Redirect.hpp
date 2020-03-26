#ifndef __REDIRECT_HPP__
#define __REDIRECT_HPP__

#include "cmd.hpp"
#include "Label.hpp"
#include "../src/Pipe.cpp"
#include "../src/Override.cpp"
#include "../src/Reverse.cpp"
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
        virtual int getLeft() { }
        virtual int getRight() { }
        virtual void setLeft(int b) { }
        virtual void setRight(int b) { }
};

#endif
