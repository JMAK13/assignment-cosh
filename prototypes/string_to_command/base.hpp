#ifndef __BASE_HPP__
#define __BASE_HPP__

class Base {
    private:  
        vector<string> commands;
        vector<char> store_ch; // Create somewhere to store the characters
        int numCmds;
        char* argList[];
        // status and pid can go here but they will move to another class later
        
    public:
        // Constructor
        Base(vector<string> cmds) {
            commands = cmds;               // Store passed in vector
            numCmds = commands.size();     // Number of commands passed in   
            char* argList[numCmds+1] = {}; // +1 Accounting for the NULL
        }
    
    
        // Convert vector of strings into vector of characters into refrence vector
        void strVec_to_args() {
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
            for(int i = 0 ; i < this->store_ch.size() ; i++){
                if(isFirst){
                    this->argList[cmdIndex] =  &(this->store_ch[i]);
                    cmdIndex++;
                    isFirst = false;
                }
                if(this->store_ch[i] == '\0') isFirst = true;
            }
        }    
        
        
        // Testing execution of commands
        void execCmd(){
            int status;  // Stores status of child process
            pid_t pid;   // Stores pid of child process            
              
            // Convert string vector to args
            strVec_to_args();
              
            // FOR PRINTING ONLY (check arguments)
            cout << "Command: " << this->argList[0] << endl;
            for(int i = 1 ; i < this->numCmds ; i++ ){
                cout << "argument #" << i << ": " << this->argList[i] << endl;
            }  
            cout << endl;  
              
            // Fill the final slot with the NULL terminator  
            argList[this->numCmds] = NULL;   
              
            // Fork new process and assign its command  
            pid = fork();
            if(pid == 0) {
                execvp(this->argList[0], this->argList); // First param is command, second is arguments
                status = 0;
                exit(0);
            }

            // Wait for child process to complete
            waitpid(pid, &status, 0);
        }  
};
#endif
