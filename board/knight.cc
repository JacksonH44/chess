#include "knight.h"

Knight::Knight(int colour, pos position) : Piece{colour, &position}, type{'n'} {}

char Knight::getType() const {
    return type;
}

bool Knight::validate(pos p, Board* board) {
    return false;
}
