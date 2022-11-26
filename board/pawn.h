#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"

class Pawn : public Piece {
    bool canPassant;
    char type;

public:
    Pawn(int colour, pos position, bool canPassant);  // Constructor

    Pawn(const Pawn& other);  // copy ctor
    
    bool validate(pos p, Board* board) override;

    bool passant();

    char getType() const override;

    Pawn *deepCopy() const override; // deep copy
};

#endif
