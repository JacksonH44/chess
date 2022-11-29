#include "cpu3.h"
#include "../game/game.h"

using namespace std;

CPU3::CPU3(int colour, Game* game) : Player{colour}, game{game} {}

tuple<pos, pos, char> CPU3::determineMove(istream& in)
{
    throw logic_error("Function not implemented yet");
}