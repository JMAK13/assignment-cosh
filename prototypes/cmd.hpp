#ifndef __CMD_HPP__
#define __CMD_HPP__

class Cmd {
    public:
        virtual void handle() = 0;
        virtual int getStatus() = 0;
        virtual pid_t getPid() = 0;
};

#endif