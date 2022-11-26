#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <tuple>
#include "../pos.h"

/** Player class representing an abstract player */
class Player {
    int colour;
    bool checked;

protected:
    //idk why determineMove was protected, I need to use it in Game

public:
    virtual std::tuple<pos, pos> determineMove() = 0;
    
    Player(int colour); // ctor

    bool isChecked();
    
    void setChecked(bool checked);
    
    int getColour();
};

#endif