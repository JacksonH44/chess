#include "piece.h"
#include "board.h"

using namespace std;

Piece::Piece(int colour, pos position):colour{colour},position{position} {} //ctor

Piece::Piece(const Piece &other) : colour{other.colour}, position{other.position}, validMoves{other.validMoves} {} // copy ctor

int Piece::getColour(){
    return this->colour;
}


bool Piece::isValidMove(pos p, Board* board){

    // Check for valid position
    if (!(((0 <= p.x) && (p.x <= 7)) && ((0 <= p.y) && (p.y <= 7)))) // Out of board dimensions
    {
        return false;
    }
    else if ((position.x == p.x) && (position.y == p.y)) // Not moving anywhere
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

vector<pos> Piece::getValidMoves() {
    return validMoves;
}

void Piece::setPos(pos p) {
    position = p;
}

pos Piece::getPos(){
    return position;
}

//Needed so we can call canCastle() on Rooks and Kings stored in Piece pointers
bool Piece::castle() {
    return false;
}

Piece::~Piece(){}
