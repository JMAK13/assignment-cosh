#ifndef __LABEL_HPP__
#define __LABEL_HPP__

#include "cmd.hpp"
// I/O requisits
#include <stdio.h>
#include <iostream>
// fork() & exec() requisits
#include <sys/types.h>
#include <unistd.h>
// exit() requisit
#include <stdlib.h>
// waitpid() requisits
#include <sys/types.h>
#include <sys/wait.h>
// exec() error requisit
#include <errno.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Label : public Cmd {
    private:
        vector<char*> args;
        int status;
        pid_t pid;
    public:
        Label() : Cmd() {
            status = -1;
        }
        
        Label(vector<char*> arguments) : Cmd() {
            for(int i = 0; i < arguments.size(); i++)
                args.push_back(arguments[i]);
            status = -1;
        }

        virtual void handle() {

            string s = args[0];
            if(s == "exit") {
                cout << "Exiting RShell...\n";
                exit(0);
                return;
            }

            pid = fork();

            if(pid == -1) cout << "Error forking\n";

            else if(pid == 0) {

                // Parse from vector into char* argList[]
                char* argList[args.size()+1] = {};

                for (int i = 0; i < args.size(); i++)
                    argList[i] = args[i];
                
                argList[args.size()]=NULL;

                int i = execvp(argList[0], argList);
                        
                if(i == -1) {
                    cout << "Could not run child process " << args[0] << endl;
                    status = -1;
                    exit(-1);
                    return;
                }
                else {
                    status = 0;
                    exit(0);
                }
            }

            else {
                waitpid(this->getPid(), &status, 0);
                return;
            }
        }

        virtual int getStatus() { return status; }
        virtual pid_t getPid() { return pid; }
        string getLabel();
};

#endif