#ifndef __OR_HPP__
#define __OR_HPP__

#include "cmd.hpp"

class Or : public Cmd {
    private:
        Cmd *l1;
        Cmd *l2;
        int status;
        pid_t pid;
    public:
        Or(Cmd* c1, Cmd* c2) : Cmd() {
            this->l1 = c1;
            this->l2 = c2;
        }

        virtual void handle() {

            int stat = this->l1->getStatus();
            
            if(stat != 0) {
                this->l2->handle();
                this->pid = this->l2->getPid();
                this->status = this->l2->getStatus();
            }
            else this->status = -1;
        }

        int getStatus() { return this->status; }
        pid_t getPid() { return this->pid; }
};

#endif