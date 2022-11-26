#include "board.h"
#include "../pos.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete theBoard[i][j];
        }
        delete[] theBoard[i];
    }
    delete[] theBoard;
}  // dtor

Board::Board() {
    theBoard = new Piece**[8];
    for (int i = 0; i < 8; ++i) {
        theBoard[i] = new Piece*[8];
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7) {
                int curColour = 0;
                if (i == 7) { curColour = 1; }  // white
                if (j == 0 || j == 7) {
                    theBoard[i][j] = new Rook{curColour, pos{i, j}, true};
                } else if (j == 1 || j == 6) {
                    theBoard[i][j] = new Knight{curColour, pos{i, j}};
                } else if (j == 2 || j == 5) {
                    theBoard[i][j] = new Bishop{curColour, pos{i, j}};
                } else if (j == 3) {
                    theBoard[i][j] = new Queen{curColour, pos{i, j}};
                } else { // j == 4; king
                    theBoard[i][j] = new King{curColour, pos{i, j}, true};
                }
            } else if (i == 1 || i == 6) {
                int curColour = 0;
                if (i == 6) { curColour = 1; } // white
                theBoard[i][j] = new Pawn{curColour, pos{i, j}, true};
            } else {
                theBoard[i][j] = nullptr;
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

int main() {
    Board* myBoard = new Board();
    delete myBoard;
    return 0;
}