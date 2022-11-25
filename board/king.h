#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King : public Piece{
    bool canCastle;

 public:
    King(int colour, pos position, bool canCastle);  // Constructor

    bool validate(pos p) override;

    bool castle();
};

#endif
