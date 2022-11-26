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

/**
 * White: 1
 * Black: 0
 * 
 * Use this when referencing colour
*/

int main() {
    int whiteWins = 0;
    int blackWins = 0;
	char winner;
    string s;
    Game* game = new Game();
    while (cin >> s){
		bool invalid = false;
		if (s == "game") {
			winner = game->play();
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
				//white
				if (s == "K") {
					p = new King(1, arraypos, false);
				}
				else if (s == "Q") {
					p = new Queen(1, arraypos);
				}
				else if (s == "R") {
					p = new Rook(1, arraypos, false);
				}
				else if (s == "N") {
					p = new Knight(1, arraypos);
				}
				else if (s == "B") {
					p = new Bishop(1, arraypos);
				}
				else if (s == "P") {
					p = new Pawn(1, arraypos, false);
				}
				//black
				else if (s == "k") {
					p = new King(0, arraypos, false);
				}
				else if (s == "q") {
					p = new Queen(0, arraypos);
				}
				else if (s == "r") {
					p = new Rook(0, arraypos, false);
				}
				else if (s == "n") {
					p = new Knight(0, arraypos);
				}
				else if (s == "b") {
					p = new Bishop(0, arraypos);
				}
				else if (s == "p") {
					p = new Pawn(0, arraypos, false);
				}
				//otherwise
				else {
					invalid = true;
				}
			}
			if (!invalid) {
				game->getBoard()->setPiece(p, arraypos);
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
				game->getBoard->setPiece(nullptr, arraypos);
			}
		}

		else if (s == "=") {
			cin >> s;
			if (s == "white") {
				game->setTurn(1);
			}
			else if (s == "black") {
				game->setTurn(0);
			}
			else {
				invalid = true;
			}
		}

		else if (s == "done") {
			// check that board is valid, then break
			cout << "not implemented yet" << endl;
		}

		else {
			invalid = true;
		}

		if (invalid) {
			cout << "invalid input" << endl;
		}
    }
}

