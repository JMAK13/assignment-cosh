#ifndef __REDIRECT_CPP__
#define __REDIRECT_CPP__

#include "../header/Redirect.hpp"


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
    int end;
    for(int i = 0; i < tree.size(); i++) {
        end = tree[i]->handle();
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
    bool prevNeedsWrite = false;
    bool needsClr = false;
    bool canPipe = true;
    bool canPipe2 = canPipe;
    for(int i = 0; i < commands.size(); i++) {

        bool isLast = true;
        int index = 0;

        if(!canPipe) {
            canPipe2 = false;
            hasConn = false;
            prevNeedsWrite = false;
            canPipe = true;
            p1.clear();
            p2.clear();
        }

        if(commands[i] == "|") {
            for(int j = i+1; j < commands.size(); j++) {
                if(commands[j] == "|" || commands[j] == ">" || commands[j] == ">>" || commands[j] == "<") {
                    if(commands[j] == "<") needsClr = true;
                    if(!canPipe2) i = commands.size();
                    j = commands.size();
                    isLast = false;
                }
                else {
                    p2.push_back(commands[j]);
                    index++;
                }
            }
            if(!needsClr) {
                i+=index;
                if(!hasConn) c1 = new Label(p1);
                else c1 = tree[tree.size()-1];
                c2 = new Label(p2);
                bool isFirst;
                if(hasConn==false) isFirst = true;
                else isFirst = false;
                c3 = new Pipe(c1, c2, isFirst, isLast);
                if(prevNeedsWrite && canPipe2) c1->setRight(c3->getRight());
                else {
                    canPipe2 = true;
                    c3->setLeft(-1);
                }
                this->addElem(c3);
                hasConn = true;
                p2.clear();
                prevNeedsWrite = true;
            }
            else {
                p1.clear();
                p2.clear();
                hasConn = false;
                prevNeedsWrite = false;
                this->tree.clear();
            }
        }
        else if(commands[i] == ">") {
            for(int j = i+1; j < commands.size(); j++) {
                if(commands[j] == "|" || commands[j] == ">" || commands[j] == ">>" || commands[j] == "<") {
                    if(commands[j] == "|") {
                        canPipe = false;
                        i++;
                    }
                    isLast = false;
                    j = commands.size();
                }
                else {
                    p2.push_back(commands[j]);
                    i++;
                }
            }
            if(!hasConn) c1 = new Label(p1);
            else c1 = tree[tree.size()-1];
            c2 = new Label(p2);
            bool isFirst;
            if(hasConn==false) isFirst = true;
            else isFirst = false;
            c3 = new Override(c1, c2, isFirst, isLast, false);
            if(prevNeedsWrite) c1->setRight(c3->getRight());
            else this->addElem(c3);
            hasConn = true;
            p2.clear();
            prevNeedsWrite = true;
        }
        else if(commands[i] == ">>") {
            for(int j = i+1; j < commands.size(); j++) {
                if(commands[j] == "|" || commands[j] == ">" || commands[j] == ">>" || commands[j] == "<") {
                    if(commands[j] == "|") canPipe = false;
                    isLast = false;
                    j = commands.size();
                }
                else {
                    p2.push_back(commands[j]);
                    i++;
                }
            }
            if(!hasConn) c1 = new Label(p1);
            else c1 = tree[tree.size()-1];
            c2 = new Label(p2);
            bool isFirst;
            if(hasConn==false) isFirst = true;
            else isFirst = false;
            c3 = new Override(c1, c2, isFirst, isLast, true);
            if(prevNeedsWrite) c1->setRight(c3->getRight());
            else this->addElem(c3);
            hasConn = true;
            p2.clear();
            prevNeedsWrite = true;
        }
        else if(commands[i] == "<") {
            for(int j = i+1; j < commands.size(); j++) {
                if(commands[j] == "|" || commands[j] == ">" || commands[j] == ">>" || commands[j] == "<") {
                    j = commands.size();
                    isLast = false;
                }
                else {
                    p2.push_back(commands[j]);
                    i++;
                }
            }
            if(!hasConn) c1 = new Label(p1);
            else c1 = tree[tree.size()-1];
            c2 = new Label(p2);
            bool isFirst;
            if(hasConn==false) isFirst = true;
            else isFirst = false;
            c3 = new Reverse(c1, c2, isFirst, isLast);
            if(prevNeedsWrite) c1->setLeft(c3->getRight());
            else this->addElem(c3);
            hasConn = true;
            p2.clear();
            prevNeedsWrite = true;
            needsClr = false;
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
