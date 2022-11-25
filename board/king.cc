#include "king.h"

King::King(int colour, pos position, bool castle): Piece{colour, &position}, canCastle{canCastle}{}

bool King::castle(){
    return canCastle;
}

bool King::validate(pos p) {
    return false;
}
