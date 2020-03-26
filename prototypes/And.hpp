#ifndef __AND_HPP__
#define __AND_HPP__

#include "label.hpp"
using namespace std;

class And : public Cmd {
    private:
        Cmd *l1;
        Cmd *l2;
        int status;
        pid_t pid;
    public:
        And(Cmd* c1, Cmd* c2) : Cmd() {
            l1 = c1;
            l2 = c2;
            status=-1;
        }

        virtual void handle() {

            int stat = l1->getStatus();
            
            if(stat == 0) {
                l2->handle();
                status = l2->getStatus();
            }
        }

        int getStatus() { return status; }
        int getPid() { return pid;}
};

#endif