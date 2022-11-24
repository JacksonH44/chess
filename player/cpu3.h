#ifndef _CPU3_H_
#define _CPU3_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** CPU3 player subclass */
class CPU3 : public Player
{
public:
    CPU3(int colour);

    std::tuple<pos, pos> determineMove() override;
};

#endif