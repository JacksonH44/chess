#include "game.h"
#include "../pos.h"
#include <iostream>
#include "../player/playerFactory.h"
#include "../player/player.h"
#include "../board/board.h"
#include <tuple>

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
    return theBoard;
}

void Game::setBoard(Board* newBoard) {
    delete theBoard;
    theBoard = newBoard;
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

char Game::play() {
    state = ongoing;
    delete whitePlayer;
    delete blackPlayer;
    string p1;
    string p2;
    cin >> p1;
    cin >> p2;
    try {
        whitePlayer = PlayerFactory::createPlayer(p1, 1);
        blackPlayer = PlayerFactory::createPlayer(p2, 0);
    }
    catch (...) {
        return 'i'; //return i for invalid setup
    }

    tuple<pos, pos> move ({0, 0}, {0, 0});
    Player* curPlayer;
    while (state == whiteChecked || state == blackChecked || state == ongoing) {
        
        if (curMove == 1) {
            curPlayer = whitePlayer;
	        //move = whitePlayer->determineMove();
        }
        else {
            //move = blackPlayer->determineMove();
            curPlayer = blackPlayer;
        }

        move = curPlayer->determineMove();
	    //if (isMovePromotion(from, to)) { // need a method in the game class to check if a move promotes a pawn
	        // prompt player for new piece
            // char newPiece = curPlayer->promptPromotion();
            
	        // validate piece, replace it on the board using setPiece()
	    //}
        //validate move
        theBoard->updateBoard(get<0>(move), get<1>(move));
	    if (state == whiteWin || state == blackWin) {
	        break;
	    }
        //game->blackPlayer->determineMove(&from, &to);
        //if (game->isMovePromotion(from, to)) {

        //}
    }//while

    if (state == whiteWin) {
        return 'w'; 
    }
    else if (state == blackWin) {
        return 'b';
    }
    else {
        return 'i';
    }
}
