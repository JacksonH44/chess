#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen:public Piece{
    bool validate(pos p);
 public:
    Queen(int colour, pos position);  // Constructor
}

#endif