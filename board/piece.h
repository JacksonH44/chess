#ifndef _PIECE_H_
#define _PIECE_H_
#include "../pos.h"
#include <iostream>

class Board;

class Piece {

protected:
   virtual bool validate(pos, Board* board) = 0;
   int colour;
   pos *position;

public:
   Piece(int colour, pos* position); // Constructor

   virtual char getType() const = 0;

   int getColour();

   bool isValidMove(pos p, Board* board);

   void setPos(pos* p);

   pos getPos();

   virtual ~Piece() = 0;

   Piece(const Piece& other); // copy ctor

   virtual Piece *deepCopy() const = 0; // Allows us to deep copy a subtype of piece without knowing which one
};

#endif

