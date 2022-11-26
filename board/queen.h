#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen : public Piece{
    
 public:
    Queen(int colour, pos position);  // Constructor

    bool validate(pos p, Board* board) override;
};

#endif
