// Internal Libraries
#include <stdio.h>     // IO
#include <iostream>    // IO
#include <sys/types.h> // fork() & exec()
#include <unistd.h>    // fork() & exec()
#include <stdlib.h>    // exit() requisit
#include <sys/wait.h>  // waitpid()
#include <errno.h>     // exec() & error()
#include <string.h>
#include <vector>

// User Libraries
#include "../src/Label.cpp"
#include "../src/And.cpp"
#include "../src/Or.cpp"
#include "../src/Dual.cpp"
#include "Redirect.cpp"
#include "../src/Container.cpp"

// Standard namespace
using namespace std;

// Function Prototypes
void tokenize(string, vector<string> &);

int main(int argc, char* argv[]) {

    string exiter="";
    bool isTest = false;
    string s;

    if(argc > 1) {
        isTest = true;
        s = "";
        for(int i = 1; i < argc; i++) {
            s += argv[i];
            if(i < argc - 1) {
                s += " ";
            }
        }
    }
    

    // Shell Loop
    do {

        vector<string> cmdLine;
        vector<Cmd*> cmds;
        vector<string> args;
        Cmd* c1=NULL;
        Cmd* c2=NULL;
        Cmd* c3=NULL;
        Cmd* c4=NULL;
        int connCnt = 0;
        bool error = false;

        cout << "RShell$ ";
        if(!isTest) {
            getline(cin, s);
        }
        else {
            cout << s <<endl;
        }
            
        // Input tokenizing
        tokenize(s, cmdLine);

        //cout<<"cmdsize (after tokenizing) = "<<cmdLine.size()<<endl;

        for(int i = 0; i<cmdLine.size(); i++) cout<<"Cmdline = "<<cmdLine[i]<<endl;

        int lefts = 0, rights = 0;
        for(int j = 0; j < cmdLine.size(); j++) {
            if(cmdLine[j] == ")") rights++;
            else if(cmdLine[j] == "(") lefts++;
        }

        if(lefts != rights) {
            cout<<"Invalid number of paranthesis\nExitting RShell..."<<endl;
            return 1;
        }

        for(int i = 0; i < cmdLine.size(); i++) {
            
            if(cmdLine[i] == "&&") {

                if(i+1 == cmdLine.size() || cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                    cout << "Invalid syntax" << endl;
                    error = true;
                } else {
                    if(connCnt == 0) c1 = new Label(args);
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    bool parNxt = false;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(j == i+1 && cmdLine[j] == "(") {
                            parNxt = true;
                            j = cmdLine.size();
                        }
                        else if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else if(cmdLine[j] == ")") {}
                        else args2.push_back(cmdLine[j]);
                    }
                    if(!parNxt) c2 = new Label(args2);
                    else if(parNxt){
                        int tmpPl = -1;

                        // Sets tmpPl to index of matching parenthesis at starting from back of
                        for(int k = i+1; k < cmdLine.size(); k++) {
                            if(cmdLine[k] == ")") {
                                tmpPl = k;
                                k = cmdLine.size()+1;
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

                        args2.push_back(cmdLine[i]);

                        c2 = new Container();
                        c2->parse(args2, false);
                    }
                    c3 = new And(c1, c2);
                    if(connCnt == 0) cmds.push_back(c1);
                    cmds.push_back(c3);
                    args.clear();
                    connCnt++;
                }
            }
            else if(cmdLine[i] == "||") {
                if(i+1 == cmdLine.size() || cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";") {
                    cout << "Invalid syntax" << endl;
                    error = true;
                } else {
                    if(connCnt == 0) c1 = new Label(args);
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    bool parNxt = false;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(j == i+1 && cmdLine[j] == "(") {
                            parNxt = true;
                            j = cmdLine.size();
                        }
                        else if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else if(cmdLine[j] == ")") {}
                        else args2.push_back(cmdLine[j]);
                    }
                    if(!parNxt) c2 = new Label(args2);
                    else if(parNxt){
                        int tmpPl = -1;

                        // Sets tmpPl to index of matching parenthesis at starting from back of
                        for(int k = i+1; k < cmdLine.size(); k++) {
                            if(cmdLine[k] == ")") {
                                tmpPl = k;
                                k = cmdLine.size()+1;
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

                        args2.push_back(cmdLine[i]);

                        c2 = new Container();
                        c2->parse(args2, false);
                    }
                    c3 = new Or(c1, c2);
                    if(connCnt == 0) cmds.push_back(c1);
                    cmds.push_back(c3);
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
                        c1 = new Label(args);
                        cmds.push_back(c1);
                    }
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    bool parNxt = false;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(j == i+1 && cmdLine[j] == "(") {
                            parNxt = true;
                            j = cmdLine.size();
                        }
                        else if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";") j = cmdLine.size();
                        else if(cmdLine[j] == ")") {}
                        else args2.push_back(cmdLine[j]);
                    }
                    if(args2.size() > 0) c2 = new Label(args2);
                    else if(parNxt) {
                        int tmpPl = -1;

                        // Sets tmpPl to index of matching parenthesis at starting from back of
                        for(int k = i+1; k < cmdLine.size(); k++) {
                            if(cmdLine[k] == ")") {
                                tmpPl = k;
                                k = cmdLine.size()+1;
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

                        args2.push_back(cmdLine[i]);
                        c2 = new Container();
                        c2->parse(args2, false);
                    }
                    if(args2.size() > 0) {
                        c3 = new Dual(c1, c2);
                        cmds.push_back(c3);
                    }
                    args.clear();
                    connCnt++;
                }
            }
            else if(cmdLine[i] == "(") {

                int tmpPl = -1;

                // Sets tmpPl to index of matching parenthesis at starting from back of
                for(int k = i; k < cmdLine.size(); k++) {
                    if(cmdLine[k] == ")") {
                        tmpPl = k;
                        k = cmdLine.size()+1;
                    }
                }

                if(tmpPl == -1) {
                    cout<<"Invalid number of parenthesis"<<endl;
                    return 1;
                }

                while(i < tmpPl) {
                    args.push_back(cmdLine[i]);
                    i++;
                }

                args.push_back(cmdLine[i]);

                c4 = new Container();
                bool test = c4->parse(args, false);

                cmds.push_back(c4);

                connCnt++;
                args.clear();
            }
            /*else if(cmdLine[i] == "|") {
                if(i+1 == cmdLine.size() || cmdLine[i-1] == "&&" || cmdLine[i-1] == "||" || cmdLine[i-1] == ";" || cmdLine[i-1] == "|") {
                    cout << "Invalid syntax" << endl;
                    error = true;
                } else {
                    if(connCnt == 0) c1 = new Label(args);
                    else c1 = cmds[cmds.size()-1];
                    vector<string> args2;
                    bool parNxt = false;
                    for(int j = i+1; j < cmdLine.size(); j++) {
                        if(j == i+1 && cmdLine[j] == "(") {
                            parNxt = true;
                            j = cmdLine.size();
                        }
                        else if(cmdLine[j] == "&&" || cmdLine[j] == "||" || cmdLine[j] == ";" || cmdLine[i-1] == "|") j = cmdLine.size();
                        else if(cmdLine[j] == ")") {}
                        else args2.push_back(cmdLine[j]);
                    }
                    if(!parNxt) c2 = new Label(args2);
                    else if(parNxt){
                        int tmpPl = -1;

                        // Sets tmpPl to index of matching parenthesis at starting from back of
                        for(int k = i+1; k < cmdLine.size(); k++) {
                            if(cmdLine[k] == ")") {
                                tmpPl = k;
                                k = cmdLine.size()+1;
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

                        args2.push_back(cmdLine[i]);

                        c2 = new Container();
                        c2->parse(args2, false);
                    }
                    c3 = new Pipe(c1, c2);
                    if(connCnt == 0) cmds.push_back(c1);
                    cmds.push_back(c3);
                    args.clear();
                    connCnt++;
                }
            }*/
            else if(cmdLine[i] != ")") {
                args.push_back(cmdLine[i]);
            }
        }

        // Pushes back if just a single Label
        if(connCnt == 0 && error == false && args.size() > 0) {
            c1 = new Redirect();
            c1->parse(args, 0);
            cmds.push_back(c1);
            args.clear();
        }

        for(int i = 0; i < cmds.size(); i++) {
            int end = cmds[i]->handle();
            if(end == 1) exiter = "exit";
        }

        cmdLine.clear();
        cmds.clear();
        args.clear();
        s="";

    } while(exiter != "exit" && !isTest);

    // Exit Program
    return 0;
}

// Tokenize function
void tokenize(string s, vector<string> &cmdLine) {
    string token = "";
    bool isChar = false;
    bool isQuote = false;
    bool isPrnt = false;
    bool isCmnt = false;

    for(int i = 0; i < s.size(); i++) {

        while(i < s.size() && (s.at(i) == ' ' || s.at(i) == '\0')) {
            if(isChar) {
                if(token != "") cmdLine.push_back(token);
                isChar = false;
            }
            token="";
            i++;
        }

        if(i >= s.size()) return;

        // Commend tokenizer
        if(s.at(i) == '#') isCmnt = true;
        if(isCmnt == true) {}
        else {
            
            // Quotes tokenizer
            if(s.at(i) == '"') {
                isQuote = true;
                i++;
                while(isQuote) {
                    token+=s.at(i);
                    i++;
                    if(s.at(i) == '"') {
                        if (s.at(i-1) == '\\') token.pop_back();
                        else isQuote = false;
                    }
                }
                cmdLine.push_back(token);
                token="";
                if(i+1 < s.size() && s.at(i+1) == ';') {
                    token+=s.at(i+1);
                    cmdLine.push_back(token);
                    i++;
                }
                token="";
                i++;
            }

            // Semi colon tokenizer
            else if(s.at(i) == ';') {
                if(token != "") cmdLine.push_back(token);
                token="";
                token+=s.at(i);
                cmdLine.push_back(token);
                token="";
            }

            // Pipe tokenizer
            else if(i > 0 && i+1 < s.size() && s.at(i) == '|' && s.at(i-1) != '|' && s.at(i+1) != '|') {
                if(token != "") cmdLine.push_back(token);
                token="";
                token+=s.at(i);
                cmdLine.push_back(token);
                token="";
            }

            // Precedence tokenizer
            else if(s.at(i) == '(') {
                if(token != "") cmdLine.push_back(token);
                token="";
                token+=s.at(i);
                cmdLine.push_back(token);
                token="";
            }
            else if(s.at(i) == ')') {
                if(token != "") cmdLine.push_back(token);
                token="";
                token+=s.at(i);
                cmdLine.push_back(token);
                token="";
            }
            
            // Else normal character
            else {
                token+=s.at(i);
                if(i+1 == s.size()) {
                    cmdLine.push_back(token);
                    return;
                }
            }
            isChar = true;
        }
    }
}
