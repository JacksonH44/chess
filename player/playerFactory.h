#ifndef _PLAYERFACTORY_H_
#define _PLAYERFACTORY_H_

#include <string>

class Player;

class PlayerFactory {
public:
    Player* createPlayer(std::string player, int colour);
};

#endif