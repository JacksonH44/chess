#ifndef _ROOK_H_
#define _ROOK_H_
#include "piece.h"

class Rook : public Piece{
    bool canCastle;
    char type;

public:
    Rook(int colour, pos position, bool canCastle);  // Constructor

    Rook(const Rook& other);  // copy ctor
    
    bool validate(pos p, Board* board) override ;

    bool castle();

    char getType() const override;

    Rook *deepCopy() const override; // deep copy
};

#endif
