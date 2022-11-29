#include "cpu2.h"
#include "../game/game.h"

using namespace std;

CPU2::CPU2(int colour, Game* game) : Player{colour}, game{game} {}

tuple<pos, pos, char> CPU2::determineMove(istream& in)
{
    throw logic_error("Function not implemented yet");
}