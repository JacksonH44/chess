#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "player.h"
#include <tuple>
#include "../pos.h"

/** Human player subclass */
class humanPlayer : Player {
public:
    tuple<pos,pos> determineMove() override;
};

#endif