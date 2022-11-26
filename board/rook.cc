#include "rook.h"

Rook::Rook(int colour, pos position, bool canCastle) : Piece{colour, &position}, canCastle{canCastle}, type{'r'} {}

bool Rook::validate(pos p, Board* board){
    return false;
}

bool Rook::castle() {
    return canCastle;
}

char Rook::getType() const {
    return type;
}