#ifndef __CMD_HPP__
#define __CMD_HPP__

#include <string>
#include <vector>

using namespace std;

class Cmd {
    protected:
        int status;
        pid_t pid;
    public:
        virtual int handle() = 0;
        virtual int getStatus() = 0;
        virtual pid_t getPid() = 0;
        virtual string getLabel() = 0;
        virtual void addElem(Cmd*) = 0;
        virtual Cmd* at(int) = 0;
        virtual int size() = 0;
        virtual bool parse(vector<string>, bool) = 0;
        virtual vector<string> getArgs() = 0;
        virtual int getLeft() = 0;
        virtual int getRight() = 0;
        virtual void setLeft(int b) = 0;
        virtual void setRight(int b) = 0;
};

#endif
