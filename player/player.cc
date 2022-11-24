#include "player.h"

Player::Player(int colour) : colour{colour}, checked{false} {}

bool Player::isChecked() {
    return checked;
}

void Player::setChecked(bool checked) {
    checked = checked;
}

int Player::getColour() {
    return colour;
}