#ifndef _CPU2_H_
#define _CPU2_H_

#include "player.h"
#include <tuple>
#include "../game/game.h"
#include <istream>
#include "../board/board.h"
#include "../board/piece.h"
#include <vector>

class Game;
struct pos;

/** CPU2 player subclass */
class CPU2 : public Player
{
Game* game;

public:
    CPU2(int colour, Game* game);
    Game* getGame();
    std::vector<pos> checkingMoves(std::vector<pos, std::allocator<pos>> availableMoves);
    std::vector<pos> capturingMoves(std::vector<pos, std::allocator<pos>> availableMoves);
    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif