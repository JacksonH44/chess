#include "board.h"
#include "../pos.h"
#include "piece.h"

Board::~Board(){}

Board::Board(const Board& other){}

Board& Board::operator=(const Board& other){
    return *this;
}

void Board::updateBoard(pos a, pos b){}

void Board::setToStart(){}

Piece& Board::getPiece(pos a){
    return this->theBoard[a.x][a.y];
}

// board needs a setPiece method that sets a piece at a position, and deletes whatever was there.
	// this function is assumed to exist in the implementation of setup mode
