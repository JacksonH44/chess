#include "knight.h"

Knight::Knight(int colour, pos position) : Piece{colour, &position}, type{'n'} {
    if (colour == 1)
    {
        type = 'N';
    }
}

char Knight::getType() const {
    return type;
}

bool Knight::validate(pos p, Board* board) {
    return false;
}
