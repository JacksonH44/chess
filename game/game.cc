#include "game.h"
#include "../pos.h"

gameState Game::getState(){
    return this->state;
}

void Game::update(pos a, pos b){}

bool Game::validate(pos a, pos b){
    return false;
}
