#ifndef __DUAL_CPP__
#define __DUAL_CPP__

#include "../header/Dual.hpp"


Dual::Dual(Cmd* c1, Cmd* c2) {
    this->l1 = c1;
    this->l2 = c2;
}

int Dual::handle() {
    if(l1->getStatus() == 1) return 1;
    int s = this->l2->handle();
    if(s == 1) return 1;
    this->pid = this->l2->getPid();
    if(this->l2->getStatus() == 0) this->status = 0;
    else this->status = -1;
    return this->status; // exit status
}

int Dual::getStatus() { return this->status; }
pid_t Dual::getPid() { return this->pid; }
string Dual::getLabel() {
    if(l2) return l2->getLabel();
    return "";
}

#endif
