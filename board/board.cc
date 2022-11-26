#include "board.h"
#include "../pos.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <ostream>
#include <cctype>

using namespace std;

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

Board::Board(const Board& other) { // copy ctor
    theBoard = new Piece**[8];
    for (int i = 0; i < 8; ++i) {
        theBoard[i] = new Piece*[8];
        for (int j = 0; j < 8; ++j) {
            theBoard[i][j] = (other.theBoard[i][j]) != nullptr ? other.theBoard[i][j]->deepCopy() : nullptr;
        }
    }
}

void Board::updateBoard(pos a, pos b) {
    Piece* curPiece = theBoard[a.x][a.y];
    if (theBoard[b.x][b.y] != nullptr) {
        delete theBoard[b.x][b.y];
    }
    theBoard[b.x][b.y] = curPiece;
}

void Board::setToStart(){}

Piece* Board::getPiece(pos a){
    return this->theBoard[a.x][a.y];
}

// method that sets piece piece at position on the board
void Board::setPiece(Piece* piece, pos position) {
    delete theBoard[position.x][position.y];
    theBoard[position.x][position.y] = piece;
}

ostream& operator<<(ostream& out, Board* board) {
    for (int i = 0; i < 8; ++i) {
        out << (8 - i) << " ";
        for (int j = 0; j < 8; ++j) {
            Piece* curPiece = board->getPiece(pos{i, j});
            if (curPiece == nullptr) {
                if ((i + j) % 2 == 1)
                {
                    out << "_"; // dark space
                }
                else
                {
                    out << " "; // white space
                }
            } else {
                out << curPiece->getType();
            }
        }
        out << endl;
    }
    out << endl;
    out << "  " << 'a' << 'b' << 'c' << 'd' << 'e' << 'f' << 'g' << 'h' << endl;
    out << endl;
    return out;
}

int main() {
    Board* myBoard = new Board();
    cout << myBoard;
    Board* myBoard2 = new Board(*myBoard);
    myBoard2->setPiece(new Queen{1, pos{4,5}}, pos{4,5});
    cout << myBoard;
    cout << myBoard2;
    delete myBoard;
    delete myBoard2;
    return 0;
}