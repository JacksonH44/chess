#include "pawn.h"

Pawn::Pawn(int colour, pos position, bool canPassant): Piece{colour, &position}, canPassant{canPassant}{}

bool Pawn::validate(pos p){
    return false;
}

bool Pawn::passant() {
    return canPassant;
}
