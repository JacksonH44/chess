#include "bishop.h"

Bishop::Bishop(int colour, pos position): Piece{colour, &position} {}

bool Bishop::validate(pos p) {
    return false;
}
