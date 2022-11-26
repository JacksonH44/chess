#include "pawn.h"

Pawn::Pawn(int colour, pos position, bool canPassant) : Piece{colour, &position}, canPassant{canPassant}, type{'p'} {
    if (colour == 1)
    {
        type = 'P';
    }
}

Pawn::Pawn(const Pawn &other) : Piece{other}, type{other.type} {} // copy ctor

Pawn *Pawn::deepCopy() const
{ // deep copy method
    return (new Pawn{*this});
}

bool Pawn::validate(pos p, Board* board){
    return false;
}

bool Pawn::passant() {
    return canPassant;
}

char Pawn::getType() const {
    return type;
}