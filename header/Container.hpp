#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

#include "cmd.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "Dual.hpp"
#include "../src/Redirect.cpp"
#include <vector>
#include <iostream>

using namespace std;

class Container : public Cmd {
    private:
        vector<Cmd*> tree;
        bool isInPar;
        int parCnt = 0;
        int parCnt1 = 0;
        int connCnt = 0;
    public:
        Container();
        virtual void addElem(Cmd*);
        virtual Cmd* at(int);
        virtual int size();
        virtual bool parse(vector<string>, bool);
        virtual int handle();
        virtual int getStatus() { return this->status; }
        virtual vector<string> getArgs() { }
        virtual pid_t getPid() { return 0; }
        virtual string getLabel() { return ""; }
        virtual int getLeft() { }
        virtual int getRight() { }
        virtual void setLeft(int b) { }
        virtual void setRight(int b) { }
};

#endif
