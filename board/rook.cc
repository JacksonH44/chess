#include "rook.h"

Rook::Rook(int colour, pos position, bool canCastle) : Piece{colour, &position}, canCastle{canCastle}, type{'r'} {
    if (colour == 1)
    {
        type = 'R';
    }
}

Rook::Rook(const Rook &other) : Piece{other}, type{other.type} {} // copy ctor

Rook *Rook::deepCopy() const
{ // deep copy method
    return (new Rook{*this});
}

void Rook::updateValidMoves(Board* board, pos p) { 
    this->position->x = p.x;
    this->position->y = p.y;
}

bool Rook::validate(pos p, Board* board){
    return false;
}

bool Rook::castle() {
    return canCastle;
}

char Rook::getType() const {
    return type;
}