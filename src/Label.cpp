#ifndef __LABEL_CPP__
#define __LABEL_CPP__

#include "../header/Label.hpp"

// Constructor
Label::Label(vector<string> cmds) {
    commands = cmds;               // Store passed in vector
    numCmds = commands.size();     // Number of commands passed in 
}

// Testing execution of commands
int Label::handle(){           
      
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
        if(isFirst) {
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
        this->status = 1;
        return this->status; // exit status //return;
    }

    // Check for test command
    else if(commands[0] == "test") {

        struct stat sb;

        if(commands.size() == 2) {
            
            int result = stat(argList[1], &sb);

            int res1 = S_ISDIR(sb.st_mode);
            int res2 = S_ISREG(sb.st_mode);

            if(res1!=0 || res2!=0) result = 1;
            else result = 0;

            if(result == 1) {
                cout<<"(True)"<<endl;
                this->status = 0;
            }
            else {
                cout<<"(False)"<<endl;
                this->status = -1;
            }

            return this->status;
        }
        else if(commands.size() == 3) {
            if(commands[1] == "-e") {
                int result = stat(argList[2], &sb);

                int res1 = S_ISDIR(sb.st_mode);
                int res2 = S_ISREG(sb.st_mode);

                if(res1!=0 || res2!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }

            else if(commands[1] == "-f") {
                int result = stat(argList[2], &sb);

                int res2 = S_ISREG(sb.st_mode);

                if(res2!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }

            else if(commands[1] == "-d") {
                int result = stat(argList[2], &sb);

                int res1 = S_ISDIR(sb.st_mode);

                if(res1!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }

            else {
                cout<<"Invalid command arguments for command: 'test'"<<endl;
                this->status = -1;
                return this->status;
            }
        }

        else {
            cout<<"Invalid number of arguments for command: 'test'"<<endl;
            this->status = -1;
            return this->status;
        }
    }

    else if(commands[0] == "[") {
        struct stat sb;

        if(commands.size() == 1 || commands[commands.size()-1] != "]") {
            cout<<"Invalid number of arguments for command: 'test'"<<endl;
            this->status = -1;
            return this->status;
        }

        else if(commands.size() == 2) {
            cout<<"Please specify a file/directory for command: 'test'"<<endl;
            this->status = -1;
            return this->status;
        }

        else if(commands.size() == 3) {
            int result = stat(argList[1], &sb);

            int res1 = S_ISDIR(sb.st_mode);
            int res2 = S_ISREG(sb.st_mode);

            if(res1!=0 || res2!=0) result = 1;
            else result = 0;

            if(result == 1) {
                cout<<"(True)"<<endl;
                this->status = 0;
            }
            else {
                cout<<"(False)"<<endl;
                this->status = -1;
            }

            return this->status;
        }

        else if(commands.size() == 4) {
            if(commands[1] == "-e") {
                int result = stat(argList[2], &sb);

                int res1 = S_ISDIR(sb.st_mode);
                int res2 = S_ISREG(sb.st_mode);

                if(res1!=0 || res2!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }

            else if(commands[1] == "-f") {
                int result = stat(argList[2], &sb);

                int res2 = S_ISREG(sb.st_mode);

                if(res2!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }

            else if(commands[1] == "-d") {
                int result = stat(argList[2], &sb);

                int res1 = S_ISDIR(sb.st_mode);

                if(res1!=0) result = 1;
                else result = 0;

                if(result == 1) {
                    cout<<"(True)"<<endl;
                    this->status = 0;
                }
                else {
                    cout<<"(False)"<<endl;
                    this->status = -1;
                }

                return this->status;
            }
        }

        else {
            cout<<"Invalid number of arguments for command: 'test'"<<endl;
            this->status = -1;
            return this->status;
        }
    }
    
    // Fork new process and assign its command
    pid = fork();
    if(pid == 0) {
        int i = execvp(argList[0], argList); // First param is command, second is arguments
        if (i == -1) {
            cout<<argList[0]<<": command not found"<<endl;
            exit(EXIT_FAILURE);
        }
        else exit(0);
    }

    // Wait for child process to complete
    else {
        waitpid(pid, &this->status, 0);
        if(this->status != 0) this->status = -1;
        else this->status = 0;
    }
    return this->status; // exit status
}

int Label::getStatus() { return this->status; }
pid_t Label::getPid() { return this->pid; }
string Label::getLabel() {
    if(commands.size() > 0) return commands[0];
    return "";
}

vector<string> Label::getArgs() {
    if(commands.size() > 0) return commands;
}

#endif
