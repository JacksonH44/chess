#include "bishop.h"

Bishop::Bishop(int colour, pos position) : Piece{colour, &position}, type{'b'} {}

char Bishop::getType() const {
    return type;
}

bool Bishop::validate(pos p, Board* board) {
    return false;
}
