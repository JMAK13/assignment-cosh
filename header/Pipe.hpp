#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include "cmd.hpp"
#include <stdio.h>     // IO
#include <iostream>    // IO
#include <sys/types.h> // fork() & exec()
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>    // fork() & exec()
#include <stdlib.h>    // exit() requisit
#include <sys/wait.h>  // waitpid()
#include <errno.h>     // exec() & error()
#include <string>
#include <vector>

using namespace std;

class Pipe : public Cmd {
    private:
        vector<string> l1;
        vector<string> l2;
        Cmd* left;
        Cmd* right;
        int pipefd[2];
        int ends[2];
        bool isLast;
        bool isFirst;
        bool writeNone;
    public:
        Pipe(Cmd*, Cmd*, bool, bool);
        virtual int handle();
        virtual int getStatus();
        virtual pid_t getPid();
        virtual string getLabel();
        virtual void addElem(Cmd*) { }
        virtual Cmd* at(int) { }
        virtual int size() { }
        virtual bool parse(vector<string>, bool) { }
        virtual vector<string> getArgs();
        virtual int getLeft() { return pipefd[0]; }
        virtual int getRight() { return pipefd[1]; }
        virtual void setLeft(int b) { if(b == -1) writeNone = true; else ends[0] = b; }
        virtual void setRight(int b) { ends[1] = b; }
};

#endif
