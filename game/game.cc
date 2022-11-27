#include "game.h"
#include "../pos.h"
#include <iostream>
#include "../player/playerFactory.h"
#include "../player/player.h"
#include "../board/board.h"
#include "../board/piece.h"
#include "../board/king.h"
#include "../board/queen.h"
#include "../board/knight.h"
#include "../board/bishop.h"
#include "../board/rook.h"
#include "../board/pawn.h" // Consider replacing all these with a pieceFactory class
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

// if the move is a promotion and the new piece is valid, swaps the new piece in and returns true
// if the move is not a promotion, returns true without swapping pieces, and false if the promotion is invalid
bool Game::handlePromotion(pos a, pos b, char piece) {
    bool invalidPiece = false;
    Piece* p = nullptr;

    if (theBoard->getPiece(a)->getType() == 'p' && b.y == 7) {
        switch (piece) {
            case 'q' :
                p = new Queen(0, a);
                break;
            case 'r' :
                p = new Rook(0, a, false);
                break;
            case 'n' :
                p = new Knight(0, a);
                break;
            case 'b' :
                p = new Bishop(0, a);
                break;
            default:
                invalidPiece = true;
        }
        if (invalidPiece) {
            delete p;
            return false;
        }
        theBoard->setPiece(p, a);
    }
    if (theBoard->getPiece(a)->getType() == 'P' && b.y == 0) {
        switch (piece) {
            case 'Q' :
                p = new Queen(1, a);
                break;
            case 'R' :
                p = new Rook(1, a, false);
                break;
            case 'N' :
                p = new Knight(1, a);
                break;
            case 'B' :
                p = new Bishop(1, a);
                break;
            default:
                invalidPiece = true;
        }
        if (invalidPiece) {
            delete p;
            return false;
        }
        theBoard->setPiece(p, a);
    }
    return true;
}

bool Game::handleCastle(pos a, pos b) {
    if (theBoard->getPiece(a)->getType() != 'k' && theBoard->getPiece(a)->getType() != 'K') {
        //not a king making the move
        return true;
    }
    int direction = (b.x - a.x)/2; // -1 for left, 1 for right
    // know that the move is laterally by 2 and the move is in turn and the king canCastle by king's validate()
    if (direction == -1) {
        if ((theBoard->getPiece({a.x-4, a.y})->getType() != 'r' && theBoard->getPiece({a.x-4, a.y})->getType() != 'R') || !theBoard->getPiece({a.x-4, a.y})->castle()) {
            //not a rook in the corner or it can't castle
            return false;
        }
        if (theBoard->getPiece({a.x-1, a.y}) != nullptr || theBoard->getPiece({a.x-2, a.y}) != nullptr || theBoard->getPiece({a.x-3, a.y}) != nullptr) {
            //something in the way
            return false;
        }
        // [check for in check, if so, return false] (can't be in check to start a castle)

        Board* snapshot = new Board(*theBoard);
        theBoard->updateBoard(a, {a.x-1, a.y}); //checking for in check on the in-between space. The end space is checked in play() after the move has been made
        // check for in check, if so, return false
        delete theBoard;
        theBoard = snapshot;
        
        //all conditions passed, move rook to where it will be after castling, then play() handles the movement of the king
        theBoard->updateBoard({0, a.y}, {3, a.y});
    }
    if (direction == 1) {
        if ((theBoard->getPiece({a.x+3, a.y})->getType() != 'r' && theBoard->getPiece({a.x+3, a.y})->getType() != 'R') || !theBoard->getPiece({a.x+3, a.y})->castle()) {
            //not a rook in the corner or it can't castle
            return false;
        }
        if (theBoard->getPiece({a.x+1, a.y}) != nullptr || theBoard->getPiece({a.x+2, a.y}) != nullptr) {
            //something in the way
            return false;
        }
        // [check for in check, if so, return false] (can't be in check to start a castle)

        Board* snapshot = new Board(*theBoard);
        theBoard->updateBoard(a, {a.x+1, a.y}); //checking for in check on the in-between space. The end space is checked in play() after the move has been made
        // check for in check, if so, return false
        delete theBoard;
        theBoard = snapshot;
        //all conditions passed, move rook to where it will be after castling, then play() handles the movement of the king
        theBoard->updateBoard({7, a.y}, {5, a.y});
    }
    return true;
}

bool Game::isBoardValid(){
    bool result = true;
    int BKings = theBoard->countPieces('k');
    int Wkings = theBoard->countPieces('K');
    // Checking if there is only one white king and one black king
    if (BKings != 1 || Wkings!= 1){
        result = false;
    }
    // Checking if there are any pawns on the last rows
    int Pawns = 0;
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard->getPiece({i, j}) != nullptr) {
                if (theBoard->getPiece({i, j})->getType() == 'p' || theBoard->getPiece({i, j})->getType() == 'P') {
                    ++Pawns;
                }
            }
        }
    }
    for (int i = 7; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard->getPiece({i, j}) != nullptr) {
                if (theBoard->getPiece({i, j})->getType() == 'p' || theBoard->getPiece({i, j})->getType() == 'P') {
                    ++Pawns;
                }
            }
        }
    }
    if (Pawns != 0){
        result = false;
    }
    // no implementation to check if either king is in check or not
    return result;
}

char Game::play() {
    
    theBoard->updateBoard(pos{-1, -1}, pos{-1, -1});
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

    cout << theBoard;

    tuple<pos, pos, char> move ({-1, -1}, {-1, -1}, ' ');
    Player* curPlayer;
    curMove = 1;
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
                pos end = get<1>(move);
                if (!(curPiece->getColour() == curMove)) 
                {
                    cout << "That is not your piece. Please make another move." << endl;
                }
                else if (curPiece->isValidMove(end, theBoard)) 
                {
                    Board* snapshot = theBoard; //this will be for checking for check after a move has been made and possibly reverting it,
                                                //it will need to use the copy constructor to actually work, but I'm not using it rn -Blake
                    if (!handlePromotion(get<0>(move), get<1>(move), get<2>(move))) {
                        cout << "You cannot promote to that piece. Please try again." << endl;
                        continue;
                    }
                    if (!handleCastle(get<0>(move), get<1>(move))) {
                        cout << "You may not castle now. Please make another move." << endl;
                        continue;
                    }
                    
                    theBoard->updateBoard(start, end);
                    gameState curState = this->getState();
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
