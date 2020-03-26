#ifndef __PIPE_CPP__
#define __PIPE_CPP__

#include "../header/Pipe.hpp"


Pipe::Pipe(Cmd* c1, Cmd* c2, bool first, bool last) {
    this->l1 = c1->getArgs();
    this->l2 = c2->getArgs();
    this->left = c1;
    this->right = c2;
    this->isFirst = first;
    this->isLast = last;
    ends[0] = -1;
    ends[1] = -1;
    writeNone = false;

    // make a pipe (fds go in pipefd[0] and pipefd[1])
    pipe(pipefd);
}

int Pipe::handle() {

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

    int stat = 0;
    int out = -1;

    if(this->isFirst) {
        int pid2 = fork();

        if(pid2 == -1) {
            // Handle fork error
        }
        else if (pid2 == 0) {

            dup2(pipefd[1], 1);
            
            int i = execvp(argList1[0], argList1);
            if (i == -1) {
                cout<<argList1[0]<<": command not found"<<endl;
                exit(EXIT_FAILURE);
            }
            else exit(0);
        }
        else {
            wait(&stat);
            close(pipefd[1]);
            close(left->getLeft());
            close(left->getRight());
        }

        if(stat > 0) stat = -1;
    }

    this->pid = fork();
    if(this->pid == -1) {
        // Handle fork error
    }
    else if(this->pid == 0) {
        
        if(!isLast) {
            close(1);
            if(ends[1] != -1) dup2(ends[1], 1);
        }
        else if(stat == -1) {
            out = open("errors.txt", O_WRONLY);
            dup2(out, 1);
            close(out);
        }
        
        close(0);
        dup2(pipefd[0], 0);
        if(writeNone) close(pipefd[0]);
        if(!isLast && ends[0] != -1) {
            close(0);
            dup2(ends[0], 0);
            close(pipefd[0]);
            close(pipefd[1]);
            close(ends[1]);
            close(left->getLeft());
            close(left->getRight());
        }

        int i = execvp(argList2[0], argList2);
        if (i == -1) {
            cout<<argList2[0]<<": command not found"<<endl;
            exit(EXIT_FAILURE);
        }
        else exit(0);
    }
    else {
        wait(&this->status);
        close(pipefd[0]);
        close(left->getLeft());
        if(ends[1] != -1) close(ends[1]);
        else if(out != -1) close(out);
        close(left->getRight());
    }

    if(this->status != 0) this->status = -1;
    else this->status = 0;
    
    return this->status;
}

int Pipe::getStatus() { return this->status; }

pid_t Pipe::getPid() { return this->pid; }

string Pipe::getLabel() {
    if(l2.size() > 0) return l2[0];
}

vector<string> Pipe::getArgs() {
    if(this->l2.size() > 0) return this->l2;
}

#endif
