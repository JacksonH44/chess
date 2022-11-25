#include "queen.h"

Queen::Queen(int colour, pos position): Piece{colour, &position} {}

bool Queen::validate(pos p){
    return false;
}
