#ifndef _PIECE_H_
#define _PIECE_H_
#include "../pos.h"
#include <iostream>
#include <vector>
#include "../pos.h"

class Board;

class Piece {

protected:
   virtual bool validate(pos, Board* board) = 0;
   int colour;
   pos position;
   std::vector<pos> validMoves;

public:
   Piece(int colour, pos position); // Constructor

   virtual char getType() const = 0;

   int getColour();

   bool isValidMove(pos p, Board* board);

   virtual void updateValidMoves(Board* board, pos p) = 0;  // Updates a list of all valid moves

   void setPos(pos p);

   pos getPos();

   virtual ~Piece() = 0;

   Piece(const Piece& other); // copy ctor

   virtual Piece *deepCopy() const = 0; // Allows us to deep copy a subtype of piece without knowing which one

   virtual bool castle(); //Needed so we can call canCastle() on Rooks and Kings stored in Piece pointers
};

#endif

