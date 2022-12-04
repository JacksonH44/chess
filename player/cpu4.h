#ifndef _CPU4_H_
#define _CPU4_H_

#include "player.h"
#include <tuple>
#include "../pos.h"
#include <istream>

class Game;

/** CPU4 player subclass */
class CPU4 : public Player
{
Game* game;

public:
    CPU4(int colour, Game* game);

    Game* getGame();

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif