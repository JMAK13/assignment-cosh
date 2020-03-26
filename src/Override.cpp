#ifndef __OVERRIDE_CPP__
#define __OVERRIDE_CPP__

#include "../header/Override.hpp"


Override::Override(Cmd* c1, Cmd* c2, bool first, bool last, bool isAppend) {
    this->l1 = c1->getArgs();
    this->l2 = c2->getArgs();
    this->left = c1;
    this->right = c2;
    this->isFirst = first;
    this->isLast = last;
    tmpFd = -1;

    // Open file with correct permissions and to override original file and to create it if it doesn't exist
    if(l2.size() > 0) {
        if(!isAppend) fd = open(l2[0].c_str(), O_WRONLY | O_TRUNC | O_CREAT);
        else fd = open(l2[0].c_str(), O_WRONLY | O_APPEND);
    }
    else {
        cout<<"No file specified"<<endl;
    }
}

int Override::handle() {

    int fds[2];
    
    vector<char> store_ch1;
    vector<char> store_ch2;

    int numCmds1 = this->l1.size();
    int numCmds2 = this->l2.size();

    // Convert string vector to args
    char* argList1[numCmds1+1]; // +1 Accounting for the NULL
    char* argList2[numCmds2+1]; // +1 Accounting for the NULL

    // Create char vector and store individual characters
    for(int i = 0 ; i < numCmds1; i++) {
        int strSize = l1[i].length()+1;
        for(int j = 0 ; j < strSize; j++) {
            store_ch1.push_back( l1[i][j] );
        }
    }

    for(int i = 0 ; i < numCmds2; i++) {
        int strSize = l2[i].length()+1;
        for(int j = 0 ; j < strSize; j++) {
            store_ch2.push_back( l2[i][j] );
        }
    }
    
    // Fill the argList with refreences to the char vector
    int cmdIndex = 0;    // Each command or argument gets its own index
    bool isFirst = true; // Checking for first letter after null terminator
    for(int i = 0 ; i < store_ch1.size() ; i++) {
        if(isFirst){
            argList1[cmdIndex] =  &(store_ch1[i]);
            cmdIndex++;
            isFirst = false;
        }
        if(store_ch1[i] == '\0') isFirst = true;
    }

    cmdIndex = 0;    // Each command or argument gets its own index
    isFirst = true; // Checking for first letter after null terminator
    for(int i = 0 ; i < store_ch2.size() ; i++) {
        if(isFirst){
            argList2[cmdIndex] =  &(store_ch2[i]);
            cmdIndex++;
            isFirst = false;
        }
        if(store_ch2[i] == '\0') isFirst = true;
    }
      
    // Fill the final slot with the NULL terminator  
    argList1[numCmds1] = NULL;
    argList2[numCmds2] = NULL;

    if(isFirst) {

        int pid2 = fork();

        if(pid2 == -1) {
            // Handle fork error
        }
        else if (pid2 == 0) {

            if(tmpFd == -1) {
                dup2(fd, 1);
            }
            else {
                if(!isFirst) close(fd);
                dup2(tmpFd, 1);
            }

            int i = execvp(argList1[0], argList1);
            if (i == -1) {
                cout<<argList1[0]<<": command not found"<<endl;
                exit(EXIT_FAILURE);
            }
            else exit(0);
        }
        else {
            wait(&this->status);
            if(tmpFd != -1) close(tmpFd);
            close(fd);
        }
    }
    else if(isLast) close(fd);

    if(this->status > 0) this->status = -1;
    else this->status = 0;
    
    return this->status;
}

int Override::getStatus() { return this->status; }

pid_t Override::getPid() { return this->pid; }

string Override::getLabel() {
    if(l2.size() > 0) return l2[0];
}

vector<string> Override::getArgs() {
    if(this->l2.size() > 0) return this->l1;
}

#endif
