#include "board.h"
#include "../pos.h"
#include "piece.h"

Board::~Board(){}  // dtor

Board::Board() {
    
}

Board::Board(const Board& other){}

Board& Board::operator=(const Board& other){
    return *this;
}

void Board::updateBoard(pos a, pos b){}

void Board::setToStart(){}

Piece* Board::getPiece(pos a){
    return this->theBoard[a.x][a.y];
}

// method that sets piece piece at position on the board
void Board::setPiece(Piece* piece, pos position) {
    delete theBoard[position.x][position.y];
    theBoard[position.x][position.y] = piece;
}
