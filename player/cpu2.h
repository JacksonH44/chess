#ifndef _CPU2_H_
#define _CPU2_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** CPU2 player subclass */
class CPU2 : Player
{
public:
    tuple<pos, pos> determineMove() override;
};

#endif