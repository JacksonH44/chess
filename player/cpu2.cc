#include "cpu2.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

CPU2::CPU2(int colour, Game* game) : Player{colour}, game{game} {}

Game* CPU2::getGame(){
    return game;
}

vector<pos> CheckingMoves(vector<pos> AvailableMoves){
    return AvailableMoves;  // not implemented yet
}

vector<pos> CapturingMoves(vector<pos> AvailableMoves){
    return AvailableMoves;  // not implemented yet
}

tuple<pos, pos, char> CPU2::determineMove(istream& in){
    vector<Piece*> AvailablePieces = getGame()->getBoard()->getPieces(this->getColour());
    int apsize = AvailablePieces.size();
    Piece* selectedPiece =  AvailablePieces[0];
    int randomPosIndex = -1;
    tuple<pos, pos, char> move = {{0, 0}, {0, 0}, ' '};
    // if there are check moves
    for(int i = 0; i < apsize; ++i){
        selectedPiece =  AvailablePieces[i];
        if (selectedPiece->getValidMoves().empty() == true){
            continue;
        }
        if (CheckingMoves(selectedPiece->getValidMoves()).empty() != true){
            pos start = selectedPiece->getPos();
            randomPosIndex = (rand() % CheckingMoves(selectedPiece->getValidMoves()).size());
            pos end = CheckingMoves(selectedPiece->getValidMoves())[randomPosIndex];
            move = {start, end, ' '};
            return move;
        }
    }
    // if there are capturing moves
    for(int j = 0; j < apsize; ++j){
        selectedPiece =  AvailablePieces[j];
        if (selectedPiece->getValidMoves().empty() == true){
            continue;
        }
        if (CapturingMoves(selectedPiece->getValidMoves()).empty() != true){
            pos start = selectedPiece->getPos();
            randomPosIndex = (rand() % CapturingMoves(selectedPiece->getValidMoves()).size());
            pos end = CapturingMoves(selectedPiece->getValidMoves())[randomPosIndex];
            move = {start, end, ' '};
            return move;
        }
    }
    // random move
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