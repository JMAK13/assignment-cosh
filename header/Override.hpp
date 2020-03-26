#ifndef __OVERRIDE_HPP__
#define __OVERRIDE_HPP__

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

class Override : public Cmd {
    private:
        vector<string> l1;
        vector<string> l2;
        Cmd* left;
        Cmd* right;
        int fd;
        int tmpFd;
        bool isLast;
        bool isFirst;
    public:
        Override(Cmd*, Cmd*, bool, bool, bool);
        virtual int handle();
        virtual int getStatus();
        virtual pid_t getPid();
        virtual string getLabel();
        virtual void addElem(Cmd*) { }
        virtual Cmd* at(int) { }
        virtual int size() { }
        virtual bool parse(vector<string>, bool) { }
        virtual vector<string> getArgs();
        virtual int getLeft() { return fd; }
        virtual int getRight() { return fd; }
        virtual void setLeft(int b) {}
        virtual void setRight(int b) { tmpFd = b; }
};

#endif
