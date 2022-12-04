#ifndef _CPU3_H_
#define _CPU3_H_

#include "player.h"
#include <tuple>
#include "../pos.h"
#include <istream>

class Game;

/** CPU3 player subclass */
class CPU3 : public Player
{
Game* game;

public:
    CPU3(int colour, Game* game); // ctor

    Game* getGame();

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif