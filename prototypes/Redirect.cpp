#ifndef __REDIRECT_CPP__
#define __REDIRECT_CPP__

#include "Redirect.hpp"


Redirect::Redirect() { }

void Redirect::addElem(Cmd* c) {
    tree.push_back(c);
}

Cmd* Redirect::at(int index) {
    if(index < tree.size()) return tree.at(index);
}

int Redirect::size() {
    return tree.size();
}

int Redirect::handle() {
    for(int i = 0; i < tree.size(); i++) {
        int end = tree[i]->handle();
        if(end == 1) {
            this->status = 1;
            return 1;
        }
    }
    
    // Sets Container status to last status in tree
    this->status = tree[tree.size()-1]->getStatus();
    
    return this->status;
}

bool Redirect::parse(vector<string> commands, bool b) {
    vector<string> p1;
    vector<string> p2;
    Cmd* c1;
    Cmd* c2;
    Cmd* c3;
    bool hasConn = false;
    bool isDone = true;
    for(int i = 0; i < commands.size(); i++) {
        if(commands[i] == "|") {
            for(int j = i+1; j < commands.size(); j++) {
                if(commands[j] == "|" || commands[j] == ">" || commands[j] == ">>" || commands[j] == "<") {
                    j = commands.size();
                    isDone = false;
                }
                else p2.push_back(commands[j]);
            }
            if(!hasConn) c1 = new Label(p1);
            else c1 = tree[tree.size()-1];
            c2 = new Label(p2);
            c3 = new Pipe(c1, c2);
            // c3->parse(p2, isDone);
            this->addElem(c3);
            hasConn = true;
            p2.clear();
        }
        else if(commands[i] == ">") {
            hasConn = true;
            for(int j = i+1; j < commands.size(); j++) {
                p2.push_back(commands[j]);
            }
        }
        else if(commands[i] == ">>") {
            hasConn = true;
            for(int j = i+1; j < commands.size(); j++) {
                p2.push_back(commands[j]);
            }
        }
        else if(commands[i] == "<") {
            hasConn = true;
            for(int j = i+1; j < commands.size(); j++) {
                p2.push_back(commands[j]);
            }
        }
        else {
            p1.push_back(commands[i]);
        }
    }

    if(!hasConn) {
        this->addElem(new Label(p1));
    }
}

int Redirect::getStatus() { return this->status; }

pid_t Redirect::getPid() { return this->pid; }

string Redirect::getLabel() {
    if(this->size() > 0) return this->at(0)->getLabel();
}

#endif
