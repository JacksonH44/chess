#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"

class Knight:public Piece{
 public:
    Knight(pieceType type, int colour, pos position);  // Constructor
    bool validate(pos p);
}

#endif