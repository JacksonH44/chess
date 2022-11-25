#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
 public:
    Bishop(int colour, pos position);  // Constructor
    
    bool validate(pos p) override;
};

#endif
