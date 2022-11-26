#ifndef _CPU4_H_
#define _CPU4_H_

#include "player.h"
#include <tuple>
#include "../pos.h"
#include <istream>

/** CPU4 player subclass */
class CPU4 : public Player
{
public:
    CPU4(int colour);

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif