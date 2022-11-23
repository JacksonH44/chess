#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King:public Piece{
    bool canCastle;
    
    bool validate(pos p);
 public:
    King(pieceType type, int colour, pos position, bool canCastle);  // Constructor
    bool canCastle();
}

#endif