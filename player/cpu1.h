#ifndef _CPU1_H_
#define _CPU1_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** CPU1 player subclass */
class CPU1 : public Player
{
public:
    CPU1(int colour); // ctor

    std::tuple<pos, pos> determineMove() override;
};

#endif