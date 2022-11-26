#include "humanPlayer.h"
#include <iostream>
#include <string>
#include <istream>
#include <tuple>
#include "../pos.h"
#include <sstream>

using namespace std;

HumanPlayer::HumanPlayer(int colour) : Player{colour} {}

tuple<pos, pos, char> HumanPlayer::determineMove(istream& in) {
    string cmd;
    while (true) {
        in >> cmd;
        if (cmd == "move")
        {
            string line;
            if (getline(in, line)) {
                istringstream iss{line};
                string start, end;
                iss >> start;
                iss >> end;
                char promotePiece;
                if (iss >> promotePiece) {
                    return tuple<pos, pos, char>{convertPos(start), convertPos(end), promotePiece};
                } else {
                    return tuple<pos, pos, char>{convertPos(start), convertPos(end), ' '};
                }
            } else {
                cout << "invalid input. try again." << endl;
            }
        }
        else if (cmd == "resign")
        {
            return tuple<pos, pos, char>{pos{-1, -1}, pos{-1, -1}, ' '};
        }
        else
        {
            cout << "invalid input. Try again." << endl;
        }
    }
}