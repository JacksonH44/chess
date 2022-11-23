#ifndef _ROOK_H_
#define _ROOK_H_
#include "piece.h"

class Rook:public Piece{
    bool canCastle;
 public:
    Rook(pieceType type, int colour, pos position, bool canCastle);  // Constructor
    bool validate(pos p);
}

#endif