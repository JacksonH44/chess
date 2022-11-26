#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King : public Piece{
    bool canCastle;
    char type;

public:
    King(int colour, pos position, bool canCastle);  // Constructor

    bool validate(pos p, Board* board) override;

    bool castle();

    char getType() const override;
};

#endif
