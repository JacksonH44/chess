#include "knight.h"

Knight::Knight(int colour, pos position): Piece{colour, &position} {}

bool Knight::validate(pos p) {
    return false;
}
