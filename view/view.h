#ifndef _VIEW_H_
#define _VIEW_H_

class View {
    virtual void printOutput() = 0;
public:
    void output() {
        printOutput();
    }  // print
};

#endif