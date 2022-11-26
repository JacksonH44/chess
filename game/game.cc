#include "game.h"
#include "../pos.h"
#include <iostream>
#include "../player/playerFactory.h"
#include "../player/player.h"
#include "../board/board.h"
#include "../board/piece.h"
#include <tuple>

using namespace std;

Game::~Game() {
    delete theBoard;
    delete blackPlayer;
    delete whitePlayer;
}

gameState Game::getState(){
    return this->state;
}

void Game::update(pos a, pos b) {}

bool Game::validate(pos a, pos b) {
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
    cout << theBoard;
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

    tuple<pos, pos, char> move ({-1, -1}, {-1, -1}, ' ');
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

        bool moveDone = false;

        while (!moveDone) {
            // NOTE: On resign, by convention, we return <pos{-1,-1}, pos{-1,-1}>
            move = curPlayer->determineMove(cin); // get player's next move
            pos start = get<0>(move);
            if (start == pos{-1, -1})
            { // player has resigned
                if (curMove == 1)
                {
                    state = blackWin;
                    moveDone = true;
                }
                else
                {
                    state = whiteWin;
                    moveDone = true;
                }
            }
            else if (theBoard->getPiece(start) == nullptr)  // No piece in the starting position
            {
                cout << "Invalid move. Please make another move." << endl;
            }
            else
            {
                Piece *curPiece = theBoard->getPiece(start);
                curPiece->setPos(&start);
                pos end = get<1>(move);
                if ((curPiece->getColour() == curMove) && (curPiece->isValidMove(end, theBoard)))
                {
                    // Board* snapshot = theBoard;
                    theBoard->updateBoard(start, end);
                    cout << theBoard;
                    moveDone = true;
                    curMove = (curMove + 1) % 2; // Flip the player's turn
                }
                else
                {
                    cout << "invalid move. Please make another move." << endl;
                }
            }
        }

        

	    //if (isMovePromotion(from, to)) { // need a method in the game class to check if a move promotes a pawn
	        // prompt player for new piece
            // char newPiece = curPlayer->promptPromotion();
            
	        // validate piece, replace it on the board using setPiece()
	    //}
        //validate move
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
