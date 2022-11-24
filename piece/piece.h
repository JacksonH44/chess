#ifndef _PIECE_H_
#define _PIECE_H_
#include "pos.h"
#include <iostream>

class Piece{
    char type;
    int colour;
    pos position;
 protected:
    virtual bool validate(pos) = 0; 
 public:
    Piece(int colour, pos position);  // Constructor
    pieceType getType();
    int getColour();
    bool isValidMove(pos p);
    void setPos(pos p);
    pos getPos();

    virtual ~Piece() = 0;
}

#endif

