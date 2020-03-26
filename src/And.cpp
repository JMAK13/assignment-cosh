#ifndef __AND_CPP__
#define __AND_CPP__

#include "../header/And.hpp"


And::And(Cmd* c1, Cmd* c2) {
    this->l1 = c1;
    this->l2 = c2;
}

int And::handle() {

    int tempSt;

    waitpid(this->l1->getPid(), &tempSt, 0);

    int stat = this->l1->getStatus();
    
    if(stat == 0) {
        int s = this->l2->handle();
        if(s == 1) return 1;
        this->pid = this->l2->getPid();
        if(this->l2->getStatus() == 0) this->status = 0;
        else this->status = -1;
    }
    else if(stat == 1) return 1;
    else this->status = -1;

    return this->status; // exit status
}

int And::getStatus() { return this->status; }
pid_t And::getPid() { return this->pid; }
string And::getLabel() {
    if(l2) return l2->getLabel();
    return "";
}

#endif
