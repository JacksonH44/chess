#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"

class Pawn:public Piece{
    bool canPassant;
 public:
    Pawn(int colour, pos position, bool canPassant);  // Constructor
    bool validate(pos p);
}

#endif
