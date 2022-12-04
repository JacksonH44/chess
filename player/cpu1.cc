#include "cpu1.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include "../pos.h"

using namespace std;

CPU1::CPU1(int colour, Game* theGame) : Player{colour}, theGame{theGame} {}

Game* CPU1::getGame(){
    return theGame;
}

tuple<pos, pos, char> CPU1::determineMove(istream& in){
    srand(time(NULL)); // random seed
    Board *theBoard = getGame()->getBoard();

    vector<Piece*> teamPieces = theBoard->getPieces(this->getColour());
    vector<Piece*> availablePieces;
    for (int i = 0; i < teamPieces.size(); ++i) {
        if (!((teamPieces[i]->getValidMoves()).empty())) {
            availablePieces.emplace_back(teamPieces[i]);
        }
    }

    vector<tuple<pos, pos>> safeMoves;

    for (int i = 0; i < availablePieces.size(); ++i) {
        Piece* selectedPiece = availablePieces[i];
        vector<pos> curValidMoves = selectedPiece->getValidMoves();
        for (int j = 0; j < curValidMoves.size(); ++j) {
            tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
            Board *snapshot = new Board(*theBoard);
            snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
            if (!snapshot->isChecked(this->getColour())) {
                safeMoves.emplace_back(move);
            }
            delete snapshot;
        }
    }

    tuple<pos, pos> selectedMove = safeMoves[rand() % safeMoves.size()];
    pos start = get<0>(selectedMove);
    pos end = get<1>(selectedMove);

    // pawn promotion
    char newPieceType = ' ';
    if ((theBoard->getPiece(start)->getType() == 'P' && end.y == 0) || (theBoard->getPiece(start)->getType() == 'p' && end.y == 7)) {
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
        if (this->getColour() == 0) {
            newPieceType += 32; // converts to lowercase if black 
        }
    }

    tuple<pos, pos, char> move = {start, end, newPieceType};
    cout << "moving " << theBoard->getPiece(start)->getType() << " from " << convertBack(start) << " to " << convertBack(end) << endl;
    return move;
}