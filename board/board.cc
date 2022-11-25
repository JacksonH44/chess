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
