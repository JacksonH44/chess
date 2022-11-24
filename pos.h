#ifndef _POS_H_
#define _POS_H_

/** a position data type for squares on the board */
struct pos {
    int x, y;
    pos(int x, int y);
};

#endif