#ifndef __BASE_HPP__
#define __BASE_HPP__

#include "cmd.hpp"

class Base : public Cmd {
    private:  
        vector<string> commands;
        vector<char> store_ch; // Create somewhere to store the characters
        int numCmds;
        int status;  // Stores status of child process
        pid_t pid;   // Stores pid of child process 
        // status and pid can go here but they will move to another class later
        
    public:
        // Constructor
        Base(vector<string> cmds) : Cmd() {
            commands = cmds;               // Store passed in vector
            numCmds = commands.size();     // Number of commands passed in 
            //this->status = -1;  
        }
        
        // Testing execution of commands
        void handle(){           
              
            // Convert string vector to args
            char* argList[numCmds+1]; // +1 Accounting for the NULL

            // Create char vector and store individual characters
            for(int i = 0 ; i < this->numCmds; i++){
                int strSize = this->commands[i].length()+1;
                for(int j = 0 ; j < strSize; j++){
                    this->store_ch.push_back( this->commands[i][j] );
                }
            }           
            
            // Fill the argList with refreences to the char vector
            int cmdIndex = 0;    // Each command or argument gets its own index
            bool isFirst = true; // Checking for first letter after null terminator
            for(int i = 0 ; i < this->store_ch.size() ; i++) {
                if(isFirst){
                    argList[cmdIndex] =  &(this->store_ch[i]);
                    cmdIndex++;
                    isFirst = false;
                }
                if(this->store_ch[i] == '\0') isFirst = true;
            }
              
            // Fill the final slot with the NULL terminator  
            argList[this->numCmds] = NULL;

            // Check for exit command
            if(commands[0] == "exit") {
                cout << "Exiting RShell..." << endl;
                return;
            }
              
            // Fork new process and assign its command  
            pid = fork();
            if(pid == 0) {
                int i = execvp(argList[0], argList); // First param is command, second is arguments
                if (i == -1) exit(-1);
                else exit(0);
            }

            // Wait for child process to complete
            else {
                waitpid(pid, &this->status, 0);
                if(this->status != 0) {
                    this->status = -1;
                }
            }
        }

        virtual int getStatus() { return this->status; }
        virtual pid_t getPid() { return this->pid; }
};
#endif