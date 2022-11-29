#include "cpu1.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

CPU1::CPU1(int colour, Game* theGame) : Player{colour}, theGame{theGame} {}

Game* CPU1::getGame(){
    return theGame;
}

tuple<pos, pos, char> CPU1::determineMove(istream& in){
    vector<Piece*> AvailablePieces = getGame()->getBoard()->getPieces(this->getColour());
    int randomPieceIndex = (rand() % AvailablePieces.size());
    Piece* randomPiece = AvailablePieces[randomPieceIndex];
    while((randomPiece->getValidMoves()).empty() == true){
        // Remove piece with no available moves 
        AvailablePieces.erase(AvailablePieces.begin() + randomPieceIndex);
        randomPieceIndex = (rand() % AvailablePieces.size());
        randomPiece = AvailablePieces[randomPieceIndex];
    }
    int randomPosIndex = (rand() % randomPiece->getValidMoves().size());
    pos start = randomPiece->getPos();
    pos end = randomPiece->getValidMoves()[randomPosIndex];

    // pawn promotion
    char newPieceType = ' ';
    if ((randomPiece->getType() == 'P' && end.y == 0) || (randomPiece->getType() == 'p' && end.y == 0)) {
        int pieceChoice = rand() % 4;
        switch(pieceChoice) {
            case 0: // Queen
                newPieceType = 'Q';
                break;
            case 1: // Rook
                newPieceType = 'R';
                break;
            case 2: // Bishop
                newPieceType = 'B';
                break;
            default: // Knight
                newPieceType = 'N';
        }
    }

    tuple<pos, pos, char> move = {start, end, newPieceType};
    return move;
}