#include "piece.h"

Piece::Piece(int colour, pos* position):colour{colour},position{position}{}

char Piece::getType(){
    return this->type;
}

int Piece::getColour(){
    return this->colour;
}

bool Piece::isValidMove(pos p){
    return validate(p);
}

void Piece::setPos(pos p){}

pos Piece::getPos(){
    return *this->position;
}

Piece::~Piece(){}
