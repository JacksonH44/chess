#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** Human player subclass */
class HumanPlayer : public Player {
public:
    HumanPlayer(int colour);

    std::tuple<pos,pos> determineMove() override;
};

#endif