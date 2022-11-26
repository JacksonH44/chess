#include "pawn.h"

Pawn::Pawn(int colour, pos position, bool canPassant) : Piece{colour, &position}, canPassant{canPassant}, type{'p'} {
    if (colour == 1)
    {
        type = 'P';
    }
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