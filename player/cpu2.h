#ifndef _CPU2_H_
#define _CPU2_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

class Game;

/** CPU2 player subclass */
class CPU2 : public Player
{
Game* game;

public:
    CPU2(int colour, Game* game);

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif