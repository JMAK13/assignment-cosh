#ifndef __DUAL_HPP__
#define __DUAL_HPP__

#include "cmd.hpp"

class Dual : public Cmd {
    private:
        Cmd *l1;
        Cmd *l2;
        int status;
        pid_t pid;
    public:
        Dual(Cmd* c1, Cmd* c2) : Cmd() {
            this->l1 = c1;
            this->l2 = c2;
        }

        virtual void handle() {
            
            this->l2->handle();
            this->pid = this->l2->getPid();
            if(this->l2->getStatus() == 0) this->status = 0;
            else this->status = -1;
        }

        int getStatus() { return this->status; }
        pid_t getPid() { return this->pid; }
};

#endif