#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
    char type;

public:
    Bishop(int colour, pos position);  // Constructor
    
    bool validate(pos p, Board* board) override;

    char getType() const override;
};

#endif
