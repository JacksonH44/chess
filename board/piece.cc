#include "piece.h"
#include "board.h"

Piece::Piece(int colour, pos* position):colour{colour},position{position}{}

int Piece::getColour(){
    return this->colour;
}


bool Piece::isValidMove(pos p, Board* board){

    // Check for valid position
    if (!(((0 <= p.x) && (p.x <= 7)) && ((0 <= p.y) && (p.y <= 7)))) // Out of board dimensions
    {
        return false;
    }
    else if ((position->x == p.x) && (position->y == p.y)) // Not moving anywhere
    {
        return false;
    }

    // Check for player killing their own piece
    Piece *curPiece = board->getPiece(p);
    if (curPiece != nullptr)
    {
        if (colour == curPiece->getColour())
        {
            return false;
        }
    }

    // Individual piece validating
    return validate(p, board);
}

void Piece::setPos(pos* p) {
    position = p;
}

pos Piece::getPos(){
    return *position;
}

Piece::~Piece(){}
