#ifndef _POS_H_
#define _POS_H_

/** a position data type for squares on the board */
struct pos {
    int x, y;
    pos(int x, int y);
};

// equality
bool operator==(const pos& pos1, const pos &pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

// inequality
bool operator!=(const pos& pos1, const pos &pos2)
{
    return !(pos1 == pos2);
}

// addition
pos operator+(const pos& pos1, const pos &pos2)
{
    return pos{pos1.x + pos2.x, pos1.y + pos2.y};
}

// subtraction
pos operator-(const pos& pos1, const pos &pos2)
{
    return pos(pos1.x - pos2.x, pos1.y - pos2.y);
}

#endif