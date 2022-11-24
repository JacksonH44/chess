#ifndef _BOARD_H_
#define _BOARD_H_

struct pos;
class Piece;

enum gameState {whiteWin, blackWin, whiteChecked, blackChecked, ongoing};

/** board class representing the chess board */
class Board {
    Piece** theBoard;
public:
    ~Board();  // dtor

    Board(const Board& other); // copy ctor

    Board& operator=(const Board& other); // copy assignment

    void updateBoard(pos a, pos b);  // add a new move onto the board

    void setToStart();  // set game board to start

    Piece getPiece(pos a);  // get specific piece

};

#endif