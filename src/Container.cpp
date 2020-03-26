#ifndef __CONTAINER_CPP__
#define __CONTAINER_CPP__

#include "../header/Container.hpp"

Container::Container() {
    isInPar = false;
}

void Container::addElem(Cmd* c) {
    tree.push_back(c);
}

Cmd* Container::at(int index) {
    if(index < tree.size()) return tree.at(index);
    return nullptr;
}

int Container::size() {
    return tree.size();
}

bool Container::parse(vector<string> cmdLine, bool isInParent) {
    vector<string> args;
    Cmd* c1=NULL;
    Cmd* c2=NULL;
    Cmd* c3=NULL;
    int connCnt = 0;
    bool error = false;
    bool isOut = isInParent;

    for(int i = 0; i < cmdLine.size(); i++) {
        if(cmdLine[i] == "&&") {
            bool par = false;
            int rights = 0;
            if(i+1 == cmdLine.size() || cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                cout << "Invalid syntax" << endl;
                error = true;
            } else {
                if(connCnt == 0) {
                    c1 = new Redirect();
                    c1->parse(args, 0);
                }
                else c1 = tree[tree.size()-1];
                vector<string> args2;
                for(int j = i+1; j < cmdLine.size(); j++) {
                    if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                    else if(cmdLine[j] == "(") {
                        par = true;
                        j = cmdLine.size();
                    }
                    else if(isInParent && cmdLine[j] == ")" ) {}
                    else args2.push_back(cmdLine[j]);
                }
                if(!par) {
                    c2 = new Redirect();
                    c2->parse(args2, 0);
                }
                else if(par){
                    int tmpPl = -1;
                    int tmpCnt = 0;

                    for(int x = i+1; x < cmdLine.size(); x++) {
                        if(cmdLine[x] == "(") rights++;
                    }

                    // Sets tmpPl to index of matching parenthesis at starting from back of
                    for(int k = i+1; k < cmdLine.size(); k++) {
                        if(cmdLine[k] == ")") {
                            tmpPl = k;
                            if(tmpCnt == rights) k = cmdLine.size()+1;
                            else tmpCnt++;
                        }
                    }

                    if(tmpPl == -1) {
                        cout<<"Invalid number of parenthesis"<<endl;
                        return 1;
                    }

                    i++;
                    while(i < tmpPl) {
                        args2.push_back(cmdLine[i]);
                        i++;
                    }

                    c2 = new Container();
                    c2->parse(args2, false);
                }
                c3 = new And(c1, c2);
                if(connCnt == 0) tree.push_back(c1);
                tree.push_back(c3);
                args.clear();
                connCnt++;
            }
        }
        else if(cmdLine[i] == "||") {
            bool par = false;
            int rights = 0;
            if(i+1 == cmdLine.size() || cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                cout << "Invalid syntax" << endl;
                error = true;
            } else {
                if(connCnt == 0) {
                    c1 = new Redirect();
                    c1->parse(args, 0);
                }
                else c1 = tree[tree.size()-1];
                vector<string> args2;
                for(int j = i+1; j < cmdLine.size(); j++) {
                    if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                    else if(cmdLine[j] == "(") {
                        par = true;
                        j = cmdLine.size();
                    }
                    else if(isInParent && cmdLine[j] == ")") {}
                    else args2.push_back(cmdLine[j]);
                }
                if(!par) {
                    c2 = new Redirect();
                    c2->parse(args2, 0);
                }
                else if(par){
                    int tmpPl = -1;
                    int tmpCnt = 0;

                    for(int x = i+1; x < cmdLine.size(); x++) {
                        if(cmdLine[x] == "(") rights++;
                    }

                    // Sets tmpPl to index of matching parenthesis at starting from back of
                    for(int k = i+1; k < cmdLine.size(); k++) {
                        if(cmdLine[k] == ")") {
                            tmpPl = k;
                            if(tmpCnt == rights) k = cmdLine.size()+1;
                            else tmpCnt++;
                        }
                    }

                    if(tmpPl == -1) {
                        cout<<"Invalid number of parenthesis"<<endl;
                        return 1;
                    }

                    i++;
                    while(i < tmpPl) {
                        args2.push_back(cmdLine[i]);
                        i++;
                    }

                    c2 = new Container();
                    c2->parse(args2, false);
                }
                c3 = new Or(c1, c2);
                if(connCnt == 0) tree.push_back(c1);
                tree.push_back(c3);
                args.clear();
                connCnt++;
            }
        }
        else if(cmdLine[i] == ";") {
            if(cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                cout << "Invalid syntax" << endl;
                error = true;
            } else {
                if(connCnt == 0) {
                    c1 = new Redirect();
                    c1->parse(args, 0);
                    tree.push_back(c1);
                }
                else c1 = tree[tree.size()-1];
                vector<string> args2;
                for(int j = i+1; j < cmdLine.size(); j++) {
                    if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";" || cmdLine[j] == "(") j = cmdLine.size();
                    else if(isInParent && cmdLine[j] == ")") {}
                    else args2.push_back(cmdLine[j]);
                }
                if(args2.size() > 0) {
                    c2 = new Redirect();
                    c2->parse(args2, 0);
                    c3 = new Dual(c1, c2);
                    tree.push_back(c3);
                }
                args.clear();
                connCnt++;
            }
        }
        else if(cmdLine[i] == "(") {
            int tmpPl = -1;
            int tmpCnt = 0;
            int rights = 0;
            int lefts = 1;

            int z = i+1;
            while(lefts != rights && z < cmdLine.size()) {
                if(cmdLine[z] == "(") lefts++;
                else if(cmdLine[z] == ")") rights++;
                args.push_back(cmdLine[z]);
                z++;
            }
            i = z-1;

            if(lefts == rights) args.pop_back();

            c3 = new Container();
            bool test = c3->parse(args, false);

            tree.push_back(c3);

            connCnt++;
            args.clear();
        }
        else if(cmdLine[i] == ")") {
            parCnt1++;
        }
        else if(cmdLine[i] != ")") {
            args.push_back(cmdLine[i]);
        }
    }

    // Pushes back if just a single Label
    if(connCnt == 0 && error == false && args.size() > 0) {
        c1 = new Redirect();
        c1->parse(args, 0);
        tree.push_back(c1);
        args.clear();
    }

    if(isOut && parCnt == parCnt1) {
        args.clear();
        parCnt = 0;
        parCnt1 = 0;
        this->isInPar = false;
    }

    return this->isInPar;
}

int Container::handle() {
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

#endif
