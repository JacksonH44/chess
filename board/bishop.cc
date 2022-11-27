#include "bishop.h"

Bishop::Bishop(int colour, pos position) : Piece{colour, &position}, type{'b'} {
    if (colour == 1)
    {
        type = 'B';
    }
}

Bishop::Bishop(const Bishop &other) : Piece{other}, type{other.type} {} // copy ctor

Bishop *Bishop::deepCopy() const
{ // deep copy method
    return (new Bishop{*this});
}

char Bishop::getType() const {
    return type;
}

void Bishop::updateValidMoves(Board* board, pos p) {
    this->position->x = p.x;
    this->position->y = p.y;
}

bool Bishop::validate(pos p, Board* board) {
    return false;
}
