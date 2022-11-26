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
    return false;
}
