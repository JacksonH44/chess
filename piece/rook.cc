#include "rook.h"

Rook::Rook(int colour, pos position, bool canCastle):colour{colour},position{position},canCastle{canCastle}{}

bool Rook::validate(pos p){
    return false;
}
