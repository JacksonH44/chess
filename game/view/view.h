#ifndef _VIEW_H_
#define _VIEW_H_

class Board;

class View {
    Board* board;
    virtual void printOutput() = 0;
public:
    void output() {
        printOutput();
    }  // print
};

#endif