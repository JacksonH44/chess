#ifndef _GAME_H_
#define _GAME_H_

class Board;
class GameView;
class Player;
struct pos;

enum gameState
{
    whiteWin,
    blackWin,
    whiteChecked,
    blackChecked,
    ongoing
};

class Game {
    int curMove;
    gameState state;
    Board* theBoard;
    GameView* theView;
    Player* whitePlayer;
    Player* blackPlayer;

public:
    gameState getState();  // get the current state of the board

    void update(pos a, pos b);  // update the board with a move

    // checks to see if a move is valid (only in the sense that it adheres to direction and blocking)
    bool validate(pos a, pos b);  
};  

#endif