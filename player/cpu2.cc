#include "cpu2.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../board/board.h"
#include "../pos.h"

using namespace std;

CPU2::CPU2(int colour, Game* game) : Player{colour}, game{game} {}

Game* CPU2::getGame(){
    return game;
}

vector<pos> CPU2::checkingMoves(vector<pos> availableMoves){
    return availableMoves;  // not implemented yet
}

vector<pos> CPU2::capturingMoves(vector<pos> availableMoves){
    return availableMoves;  // not implemented yet
}

// tuple<pos, pos, char> CPU2::determineMove(istream& in){
//     vector<Piece*> availablePieces = getGame()->getBoard()->getPieces(this->getColour());
//     int apsize = availablePieces.size();
//     Piece* selectedPiece =  availablePieces[0];
//     int randomPosIndex = -1;
//     tuple<pos, pos, char> move = {{0, 0}, {0, 0}, ' '};
//     vector<pos> curValidMoves = selectedPiece->getValidMoves();

//     // if there are check moves
//     for(int i = 0; i < apsize; ++i){
//         selectedPiece =  availablePieces[i];
//         if (curValidMoves.empty()){
//             continue;
//         }
//         vector<pos> curCheckingMoves = checkingMoves(curValidMoves);
//         if (!(curCheckingMoves.empty())) { // there are checking moves
//             pos start = selectedPiece->getPos();
//             randomPosIndex = (rand() % curCheckingMoves.size());
//             pos end = curCheckingMoves[randomPosIndex];
//             move = {start, end, ' '};
//             return move;
//         }
//     }
//     // if there are capturing moves
//     for(int j = 0; j < apsize; ++j){
//         selectedPiece =  availablePieces[j];
//         if (curValidMoves.empty()){
//             continue;
//         }
//         vector<pos> curCapturingMoves = capturingMoves(curValidMoves);
//         if (!(curCapturingMoves.empty())) {
//             pos start = selectedPiece->getPos();
//             randomPosIndex = (rand() % curCapturingMoves.size());
//             pos end = curCapturingMoves[randomPosIndex];
//             move = {start, end, ' '};
//             return move;
//         }
//     }
//     // random move
//     int randomPieceIndex = (rand() % availablePieces.size());
//     Piece* randomPiece = availablePieces[randomPieceIndex];
//     while((randomPiece->getValidMoves()).empty()){
//         // Remove piece with no available moves 
//         availablePieces.erase(availablePieces.begin() + randomPieceIndex);
//         randomPieceIndex = (rand() % availablePieces.size());
//         randomPiece = availablePieces[randomPieceIndex];
//     }
//     randomPosIndex = (rand() % randomPiece->getValidMoves().size());
//     pos start = randomPiece->getPos();
//     pos end = randomPiece->getValidMoves()[randomPosIndex];

//     // pawn promotion
//     char newPieceType = ' ';
//     if ((randomPiece->getType() == 'P' && end.y == 0) || (randomPiece->getType() == 'p' && end.y == 0)) {
//         int pieceChoice = rand() % 4;
//         switch(pieceChoice) {
//             case 0: // Queen
//                 newPieceType = 'Q';
//                 break;
//             case 1: // Rook
//                 newPieceType = 'R';
//                 break;
//             case 2: // Bishop
//                 newPieceType = 'B';
//                 break;
//             default: // Knight
//                 newPieceType = 'N';
//         }
//     }

//     move = {start, end, newPieceType};
//     return move;
// }


tuple<pos, pos, char> CPU2::determineMove(istream& in){
    Board *theBoard = getGame()->getBoard();

    vector<Piece*> teamPieces = theBoard->getPieces(this->getColour());
    vector<Piece*> availablePieces;
    for (int i = 0; i < teamPieces.size(); ++i) {
        if (!((teamPieces[i]->getValidMoves()).empty())) {
            availablePieces.emplace_back(teamPieces[i]);
        }
    }

    vector<tuple<pos, pos>> preferredMoves;
    vector<tuple<pos, pos>> safeMoves;

    for (int i = 0; i < availablePieces.size(); ++i) {
        Piece* selectedPiece = availablePieces[i];
        vector<pos> curValidMoves = selectedPiece->getValidMoves();
        for (int j = 0; j < curValidMoves.size(); ++j) {
            if (theBoard->getPiece(curValidMoves[j]) != nullptr) { //capturing move
                tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
                Board *snapshot = new Board(*theBoard);
                snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
                if (!snapshot->isChecked(this->getColour())) {
                    preferredMoves.emplace_back(move);
                }
                delete snapshot;
            }
            else {
                // look for checkng move
                Board *snapshot = new Board(*theBoard);
                snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
                if (snapshot->isChecked(this->getColour())) {
                    delete snapshot;
                    continue; // go next if this move puts us in check
                }
                pos opKingPos = {-1, -1};
                if (this->getColour() == 1) { // opponent has black king
                    opKingPos = snapshot->findPiece('k');
                } else { // opponent has white king
                    opKingPos = snapshot->findPiece('K');
                }
                tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
                if (selectedPiece->isValidMove(opKingPos, snapshot)) { //checking move
                    preferredMoves.emplace_back(move);
                }
                else {
                    safeMoves.emplace_back(move); // non-checking or capturing move but doesn't put us in check
                }
                delete snapshot;
            }
        }
    }

    pos start = {-1, -1};
    pos end = {-1, -1};
    if (!(preferredMoves.empty())) { // if any capturing or checking moves exist, pick a random one
        tuple<pos, pos> selectedMove = preferredMoves[rand() % preferredMoves.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    else { // otherwise, pick any move
        tuple<pos, pos> selectedMove = safeMoves[rand() % safeMoves.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    // the fact that we aren't in checkmate means there must be at least one available move, so we don't need
    // to worry about the case where both preferredMoves and safeMoves are empty. If preferredMoves is empty,
    // then safeMoves must not be

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