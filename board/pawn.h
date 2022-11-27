#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <vector>
#include "../pos.h"

class Pawn : public Piece {
    bool canPassant;
    char type;

public:
    Pawn(int colour, pos position, bool canPassant);  // Constructor

    Pawn(const Pawn& other);  // copy ctor
    
    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;  // Updates a list of all valid moves

    bool passant();

    char getType() const override;

    Pawn *deepCopy() const override; // deep copy
};

#endif
