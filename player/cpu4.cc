#include "cpu4.h"
#include "../game/game.h"

using namespace std;

CPU4::CPU4(int colour, Game* game) : Player{colour}, game{game} {}

tuple<pos, pos, char> CPU4::determineMove(istream& in)
{
    throw logic_error("Function not implemented yet");
}