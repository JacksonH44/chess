#include "knight.h"

Knight::Knight(int colour, pos position) : Piece{colour, &position}, type{'n'} {
    if (colour == 1)
    {
        type = 'N';
    }
}

Knight::Knight(const Knight &other) : Piece{other}, type{other.type} {} // copy ctor

Knight *Knight::deepCopy() const
{ // deep copy method
    return (new Knight{*this});
}

char Knight::getType() const {
    return type;
}

bool Knight::validate(pos p, Board* board) {
    int xDist = position->x - p.x;
    int yDist = position->y - p.y;
    if ((abs(xDist) == 2 && abs(yDist) == 1) || (abs(xDist) == 1 && abs(yDist) == 2)) {
        return true;  // In an L-shape
    } else {
        return false;
    }
}
