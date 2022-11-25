#include "main.h"
#include <iostream>
#include <string>
#include "player/player.h"
#include "player/playerFactory.h"
#include "board/board.h"
#include "pos.h"
#include "game/game.h"
#include "board/king.h"
#include "board/queen.h"
#include "board/knight.h"
#include "board/bishop.h"
#include "board/rook.h"
#include "board/pawn.h"

using namespace std;

int main() {
    int whiteWins = 0;
    int blackWins = 0;
    string s;
    Game* game = new Game();
    while (cin >> s){
	bool invalid = false;
        if (s == "game") {
	    Player* player1 = nullptr;
	    Player* player2 = nullptr;
	    string p1;
	    string p2;
	    cin >> p1;
	    cin >> p2;
	    try {
	        //player1 = PlayerFactory::createPlayer(p1);
		//player2 = PlayerFactory::createPlayer(p2);
	    }
	    catch (...) {
		invalid = true;
		delete player1;
		delete player2;
		break;
	    }

	    if (!invalid) {
		//game->whitePlayer = player1; NEED EITHER PLAYERS TO BE PUBLIC OR DO THE GAME LOOP IN GAME.CC
		//game->blackPlayer = player2;
		//gameLoop(game);
	    }
	}
        else if (s == "setup") {
	    //void setupLoop(game);
	}
	else {
	    invalid = true;
	}
	if (invalid) {
	    cout << "invalid input" << endl;
	}
    }//while

    cout << "Final Score:" << endl;
    cout << "White: " << whiteWins << endl;
    cout << "Black: " << blackWins << endl;

    return 0;
}

char gameLoop(Game* game) { //main game loop. Handles turns, moves, etc
    pos from = {0, 0};
    pos to = {0, 0};
    while (game->getState() >= 2 && game->getState() <= 4) {
	//game->whitePlayer->determineMove(&from, &to); // determineMove should be void since it needs to return two positions through pointers
	//if (game->isMovePromotion(from, to)) { // need a method in the game class to check if a move promotes a pawn
	    // prompt player for new piece
	    // validate piece, replace it on the board using setPiece()
	//}
	if (game->getState() < 2) {
	    break;
	}
	//game->blackPlayer->determineMove(&from, &to);
	//if (game->isMovePromotion(from, to)) {

	//}
    }
    return 'w'; //white wins, obviously change this later
}

void setupLoop(Game* game) {
    string s;
    int colour = 1;
    // remove all pieces from game.board
    while (cin >> s) {
	bool invalid = false;
	string chesspos = "";
	if (s == "+") {
	    cin >> s;
	    cin >> chesspos;
	    pos arraypos = {0, 0};
	    try {
		arraypos = convertPos(chesspos);
	    }
	    catch(...) {
		invalid = true;
	    }
	    if (!invalid) {
		Piece* p = nullptr;
		if (s == "K") {
		    p = new King(colour, arraypos, false);
		}
		else if (s == "Q") {
		    p = new Queen(colour, arraypos);
		}
		else if (s == "r") {
		    p = new Rook(colour, arraypos, false);
		}
		else if (s == "k") {
		    p = new Knight(colour, arraypos);
		}
		else if (s == "b") {
		    p = new Bishop(colour, arraypos);
		}
		else if (s == "p") {
		    p = new Pawn(colour, arraypos, false);
		}
		else {
		    invalid = true;
		}
	    }
	    if (!invalid) {
		// game.board->setPiece(p, arraypos);
	    }
	}
	else if (s == "-") {
	    cin >> chesspos;
	    try {
		pos arraypos = convertPos(chesspos);
	    }
	    catch(...) {
		invalid = true;
	    }
	    if (!invalid) {
		// game.board->setPiece(nullptr, arraypos);
	    }
	}
	else if (s == "=") {
	    if (colour == 1) {
		colour = 0;
	    }
	    else {
		colour = 1;
	    }
	}
	else if (s == "done") {
	    // check that board is valid, then break
	}
	else {
	    invalid = true;
	}
	if (invalid) {
	    cout << "invalid input" << endl;
	}
    }
}

