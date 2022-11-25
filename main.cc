#include "main.h"
#include <iostream>
#include "player/player.h"
#include "player/playerFactory.h"

using namespace std;

int main() {
    int whiteWins = 0;
    int blackWins = 0;
    string s;
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
		gameLoop(player1, player2);
	    }
	}
        else if (s == "setup") {
	    // enter setup mode
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

char gameLoop(Player* white, Player* black) { //main game loop. Handles turns, moves, etc
    // create game object
    // where does board come from?
    return 'w'; //white wins
}
