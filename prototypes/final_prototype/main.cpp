#include <stdio.h>     // IO
#include <iostream>    // IO
#include <sys/types.h> // fork() & exec()
#include <unistd.h>    // fork() & exec()
#include <stdlib.h>    // exit() requisit
#include <sys/types.h> // waitpid()
#include <sys/wait.h>  // waitpid()
#include <errno.h>     // exec() & error()
#include <string.h>
#include <vector>

// Standard namespace
using namespace std;

// User Libraries
#include "Label.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "Dual.hpp"

// Utility Functions
void tokenize(string, vector<string> &);

int main(int argc, char* argv[]) {

    string exiter="";

    // Shell Loop
    do {

        // Declare shell variables
        string s;
        vector<string> cmdLine;

        // Print shell and take in input
        cout << "RShell$ ";
        getline(cin, s);
        
        // Tokenize input
        tokenize(s, cmdLine);

        // Parses tokens to object instances, utilizing composite design
        vector<Cmd*> cmds;
        vector<string> args;
        Cmd* c1=NULL;
        Cmd* c2=NULL;
        Cmd* c3=NULL;
        int connCnt = 0;
        bool syError = false;
        for(int i = 0; i < cmdLine.size(); i++) {

            // Parses '&&' connector
            if(cmdLine[i] == "&&") {
                if(cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                    cout << "Invalid syntax" << endl;
                    syError = true;
                } else {
                    if(connCnt == 0) c1 = new Label(args);
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else args2.push_back(cmdLine[j]);
                    }
                    c2 = new Label(args2);
                    c3 = new And(c1, c2);
                    if(connCnt == 0) cmds.push_back(c1);
                    cmds.push_back(c3);
                    args.clear();
                    connCnt++;
                }
            }

            // Parses '||' connector
            else if(cmdLine[i] == "||") {
                if(cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                    cout << "Invalid syntax" << endl;
                    syError = true;
                } else {
                    if(connCnt == 0) c1 = new Label(args);
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else args2.push_back(cmdLine[j]);
                    }
                    c2 = new Label(args2);
                    c3 = new Or(c1, c2);
                    if(connCnt == 0) cmds.push_back(c1);
                    cmds.push_back(c3);
                    args.clear();
                    connCnt++;
                }
            }

            // Parses ';' connector
            else if(cmdLine[i] == ";") {
                if(cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                    cout << "Invalid syntax" << endl;
                    syError = true;
                } else {
                    if(connCnt == 0) {
                        c1 = new Label(args);
                        cmds.push_back(c1);
                    }
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else args2.push_back(cmdLine[j]);
                    }
                    if(args2.size() > 0) {
                        c2 = new Label(args2);
                        c3 = new Dual(c1, c2);
                        cmds.push_back(c3);
                    }
                    args.clear();
                    connCnt++;
                }
            }
            
            else {
                args.push_back(cmdLine[i]);
            }
        }

        // Handles single command no connectors case
        if(connCnt == 0 && syError == false && args.size() > 0) {
            c1 = new Label(args);
            cmds.push_back(c1);
            args.clear();
        }

        // Handles custom exit command for RShell
        int i = 0;
        while(i < cmdLine.size() && exiter != "exit") {
            if(cmdLine[i] == "exit") exiter = cmdLine[i];
            i++;
        }

        // Calls each command
        if(syError == false) {
            for(int i = 0; i < cmds.size(); i++) cmds[i]->handle();
        }

    // Loop condition
    } while(exiter != "exit");

    // Exit Program
    return 0;
}


// Tokenizes string input, puts 'tokens' into cmdLine vector
void tokenize(string s, vector<string> &cmdLine) {\
    const char* input = s.c_str();
    string token = "";
    bool isChar = false;
    bool isQuote = false;
    bool isCmnt = false;

    for(int i = 0; i < strlen(input)+1; i++) {

        while(input[i] == ' ' || input[i] == '\0') {
            if(isChar) {
                if(token != "") cmdLine.push_back(token);
                isChar = false;
            }
            token="";
            i++;
        }

        if(input[i] == '#') isCmnt = true;
        if(isCmnt == true) {}
        else {
            
        // Checking for quotes         
        if(input[i] == '"'){
            isQuote = true;
            i++;
            while(isQuote){
                token+=(input[i]);
                i++;
                if(input[i] == '"') isQuote = false;
            }
            cmdLine.push_back(token);
            token="";
            if(input[i+1] == ';') {
                token+=input[i+1];
                cmdLine.push_back(token);
                i++;
            }
            token="";
            i++;
        }

        // Corrects tokenizing of semi colons
        else if(input[i] == ';') {
            if(token != "") cmdLine.push_back(token);
            token="";
            token+=input[i];
            cmdLine.push_back(token);
            token="";
            i++;
        }
        
        // Else normal character
        else token+=(input[i]);
        isChar = true;
        }
    }
}