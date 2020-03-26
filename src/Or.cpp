#ifndef __OR_CPP__
#define __OR_CPP__

#include "../header/Or.hpp"


Or::Or(Cmd* c1, Cmd* c2) {
    this->l1 = c1;
    this->l2 = c2;
}

int Or::handle() {

    int tempSt;

    waitpid(this->l1->getPid(), &tempSt, 0);

    int stat1 = this->l1->getStatus();
    int stat2;
    
    if(stat1 != 0) {
        
        if(stat1 == 1) {
            this->status = 1;
            return 1;
        }

        stat2 = this->l2->handle();
        if(stat2 != 0) {
            if(stat2 == 1) {
                this->status=1;
                return 1;
            }
            else this->status = -1;
        }
        else this->status = 0;

        this->pid = this->l2->getPid();
    }
    else this->status = 0;

    return this->status; // exit status
}

int Or::getStatus() { return this->status; }
pid_t Or::getPid() { return this->pid; }
string Or::getLabel() {
    if(l2) return l2->getLabel();
    return "";
}

#endif
