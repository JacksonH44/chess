#include "game.h"
#include "../pos.h"
#include <iostream>

using namespace std;

gameState Game::getState(){
    return this->state;
}

void Game::update(pos a, pos b){}

bool Game::validate(pos a, pos b){
    return false;
}

void Game::setTurn(int colour) {
    curMove = colour;
}

Board* Game::getBoard() {
    return board;
}

void setBoard(Board* newBoard) {
    delete board;
    board = newBoard;
}

bool isMovePromotion(pos* from, pos* to) {
    // if (board->pieceAt(from)->getChar() == 'p' && to->y == 7) {
    //     return true;
    // }
    // if (board->pieceAt(from)->getChar() == 'P' && to->y == 0) {
    //     return true;
    // }
    return false;
}

char Game::play(int turn) {
    state = 4;
    delete whitePlayer;
    delete blackPlayer;
    string p1;
    string p2;
    cin >> p1;
    cin >> p2;
    try {
        whitePlayer = PlayerFactory::createPlayer(p1);
        blackPlayer = PlayerFactory::createPlayer(p2);
    }
    catch (...) {
        return 'i'; //return i for invalid setup
    }

    pos from = {0, 0};
    pos to = {0, 0};
    Player* curPlayer;
    while (state >= 2 && state <= 4) {
        
        if (curMove == 1) {
            curPlayer = whitePlayer;
	        whitePlayer->determineMove(&from, &to); // determineMove should be void since it needs to return two positions through pointers
        }
        else {
            blackPlayer->determineMove(&from, &to);
            curPlayer = blackPlayer;
        }

        curPlayer->determineMove(&from, &to);
	    //if (isMovePromotion(from, to)) { // need a method in the game class to check if a move promotes a pawn
	        // prompt player for new piece
            // char newPiece = curPlayer->promptPromotion();
            
	        // validate piece, replace it on the board using setPiece()
	    //}
        //validate move
        board->updateBoard(from, to);
	    if (getState() < 2) {
	        break;
	    }
        //game->blackPlayer->determineMove(&from, &to);
        //if (game->isMovePromotion(from, to)) {

        //}
    }//while

    if (state == 0) {
        return 'w'; 
    }
    else if (state == 1) {
        return 'b';
    }
    else {
        return 'i';
    }
}
