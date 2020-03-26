#ifndef __AND_HPP__
#define __AND_HPP__

#include "cmd.hpp"

class And : public Cmd {
    private:
        Cmd* l1;
        Cmd* l2;
    public:
        And(Cmd* c1, Cmd* c2);
        virtual int handle();
        virtual int getStatus();
        virtual pid_t getPid();
        virtual string getLabel();
        virtual void addElem(Cmd*) { }
        virtual vector<string> getArgs() { }
        virtual Cmd* at(int) { return nullptr; }
        virtual int size() { return 0; }
        virtual bool parse(vector<string>, bool) { return false; }
        virtual int getLeft() { }
        virtual int getRight() { }
        virtual void setLeft(int b) { }
        virtual void setRight(int b) { }
};

#endif
