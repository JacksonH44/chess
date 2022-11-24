#include "pawn.h"

Pawn::Pawn(int colour, pos position, bool canPassant):colour{colour},position{position},canPassant{canPassant}{}

bool Pawn::validate(pos p){
    return false;
}
