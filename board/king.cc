#include "king.h"

King::King(int colour, pos position, bool castle) : Piece{colour, &position}, canCastle{canCastle}, type{'k'} {
    if (colour == 1)
    {
        type = 'K';
    }
}

King::King(const King &other) : Piece{other}, type{other.type} {} // copy ctor

King *King::deepCopy() const
{ // deep copy method
    return (new King{*this});
}

bool King::castle(){
    return canCastle;
}

char King::getType() const
{
    return type;
}

void King::updateValidMoves(Board* board, pos p) {
    this->position->x = p.x;
    this->position->y = p.y;
}

bool King::validate(pos p, Board* board) {
    return false;
}
