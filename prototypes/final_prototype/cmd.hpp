#ifndef __CMD_HPP__
#define __CMD_HPP__

class Cmd {
    private:
        int status;
        pid_t pid;
    protected:
        vector<string> commands;
        vector<char> store_ch;      // Create somewhere to store the characters
    public:
        virtual void handle() = 0;
        virtual int getStatus() = 0;
        virtual pid_t getPid() = 0;
};

#endif