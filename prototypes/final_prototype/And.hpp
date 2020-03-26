#ifndef __AND_HPP__
#define __AND_HPP__

#include "cmd.hpp"

class And : public Cmd {
    private:
        Cmd *l1;
        Cmd *l2;
        int status;
        pid_t pid;
    public:
        And(Cmd* c1, Cmd* c2) : Cmd() {
            this->l1 = c1;
            this->l2 = c2;
        }

        virtual void handle() {

            int stat = this->l1->getStatus();
            
            if(stat == 0) {
                this->l2->handle();
                this->pid = this->l2->getPid();
                if(this->l2->getStatus() == 0) this->status = 0;
                else this->status = -1;
            }
            else this->status = -1;
        }

        int getStatus() { return this->status; }
        pid_t getPid() { return this->pid; }
};

#endif