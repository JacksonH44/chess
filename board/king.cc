#include "king.h"

King::King(int colour, pos position, bool castle) : Piece{colour, &position}, canCastle{canCastle}, type{'k'} {
    if (colour == 1)
    {
        type = 'K';
    }
}

bool King::castle(){
    return canCastle;
}

char King::getType() const
{
    return type;
}

bool King::validate(pos p, Board* board) {
    return false;
}
