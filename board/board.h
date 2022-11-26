#ifndef _BOARD_H_
#define _BOARD_H_
#include <ostream>

struct pos;
class Piece;

/** board class representing the chess board */
class Board {
    Piece*** theBoard;

public:
    Board(); // ctor

    ~Board();  // dtor

    Board(const Board& other); // copy ctor

    void updateBoard(pos a, pos b);  // add a new move onto the board

    void setToStart();  // set game board to start

    Piece* getPiece(pos a);  // get specific piece

    void setPiece(Piece* piece, pos position);

    int countPieces(char type);  // Function that counts how many occurrences of a certain type there are

    friend std::ostream& operator<<(std::ostream& out, Board* board);  // TEMP: Remove once view is implemented

};

#endif