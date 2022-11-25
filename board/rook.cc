#include "rook.h"

Rook::Rook(int colour, pos position, bool canCastle): Piece{colour, &position}, canCastle{canCastle}{}

bool Rook::validate(pos p){
    return false;
}

bool Rook::castle() {
    return canCastle;
}