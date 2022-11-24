#ifndef _CPU4_H_
#define _CPU4_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** CPU4 player subclass */
class CPU4 : Player
{
public:
    tuple<pos, pos> determineMove() override;
};

#endif