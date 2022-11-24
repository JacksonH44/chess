#ifndef _BOARD_H_
#define _BOARD_H_

struct pos;
class Piece;

enum gameState {whiteWin, blackWin, whiteChecked, blackChecked, ongoing};

/** board class representing the chess board */
class Board {
    Piece** theBoard;
public:
    void updateBoard(pos a, pos b);  // add a new move onto the board

    gameState getState();  // get current state of the game

    void setToStart();  // set game board to start

    Piece getPiece(pos a);  // get specific piece

};

#endif