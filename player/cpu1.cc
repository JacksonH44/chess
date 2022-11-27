#include "cpu1.h"

using namespace std;

CPU1::CPU1(int colour, Game* theGame) : Player{colour}, theGame{theGame} {}

Game* CPU1::getGame(){
    return theGame;
}

tuple<pos, pos, char> CPU1::determineMove(istream& in){
    vector<Piece*> AvailablePieces = getGame()->getBoard()->getPieces(this->getColour());
    int randomPieceIndex = (rand() % AvailablePieces.size());
    Piece* randomPiece = AvailablePieces[randomPieceIndex-1];
    while(randomPiece->getValidMoves().empty() == true){
        randomPieceIndex = (rand() % AvailablePieces.size());
        Piece* randomPiece = AvailablePieces[randomPieceIndex-1];
    }
    int randomPosIndex = (rand() % randomPiece->getValidMoves().size());
    pos start = randomPiece->getPos();
    pos end = randomPiece->getValidMoves()[randomPosIndex-1];
    tuple<pos, pos, char> move ={start, end, ' '};
    return move;
}