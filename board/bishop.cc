#include "bishop.h"

Bishop::Bishop(int colour, pos position) : Piece{colour, &position}, type{'b'} {
    if (colour == 1)
    {
        type = 'B';
    }
}

char Bishop::getType() const {
    return type;
}

bool Bishop::validate(pos p, Board* board) {
    return false;
}
