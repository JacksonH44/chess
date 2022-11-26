#ifndef _POS_H_
#define _POS_H_

#include <string>

/** a position data type for squares on the board */
struct pos {
    int x, y;

    pos(int x, int y); // ctor

    bool operator==(const pos& other);  // equality

    bool operator!=(const pos& other); // inequality

    pos& operator=(const pos& other);  // copy assignment
};

pos convertPos(std::string& s);

#endif
