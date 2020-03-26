#ifndef __LABEL_HPP__
#define __LABEL_HPP__

#include "cmd.hpp"
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

using namespace std;

class Label : public Cmd {
    private:  
        vector<string> commands;
        vector<char> store_ch; // Create somewhere to store the characters
        int numCmds;
        
    public:
        Label(vector<string> cmds);
        virtual int handle();
        virtual int getStatus();
        virtual pid_t getPid();
        virtual string getLabel();
        virtual void addElem(Cmd*) { }
        virtual vector<string> getArgs();
        virtual Cmd* at(int) { return nullptr; }
        virtual int size() { return 0; }
        virtual bool parse(vector<string>, bool) { return false; }
        virtual int getLeft() { }
        virtual int getRight() { }
        virtual void setLeft(int b) { }
        virtual void setRight(int b) { }
};
#endif
