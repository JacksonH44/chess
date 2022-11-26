#include "board.h"
#include "../pos.h"
#include "piece.h"
#include "rook.h"

Board::~Board(){}  // dtor

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7) {
                int curColour = 0;
                if (i == 1) { curColour = 1; }
                if (j == 0) {
                    theBoard[i][j] = new Rook{curColour, pos{i, j}, true};
                }
            } else if (i == 1 || i == 6) {
                if (j == 0) {
                    
                }
            }
        }
    }
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
