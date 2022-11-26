#ifndef _PIECE_H_
#define _PIECE_H_
#include "../pos.h"
#include <iostream>

class Board;

class Piece {

protected:
   virtual bool validate(pos, Board* board) = 0;
   char type;
   int colour;
   pos *position;

public:
   Piece(int colour, pos* position); // Constructor

   char getType();

   int getColour();

   bool isValidMove(pos p, Board* board);

   void setPos(pos p);

   pos getPos();

   virtual ~Piece() = 0;
};

#endif

