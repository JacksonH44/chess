#include "king.h"

King::King(int colour, pos position, bool canCastle):colour{colour},position{position},canCastle{canCastle}{}

bool King::canCastle(){
    return false;
}
