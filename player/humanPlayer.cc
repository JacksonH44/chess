#include "humanPlayer.h"

HumanPlayer::HumanPlayer(int colour) : Player{colour} {}

std::tuple<pos, pos> HumanPlayer::determineMove() {
    throw std::logic_error("Function not implemented yet");
}