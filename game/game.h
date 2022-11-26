#ifndef _GAME_H_
#define _GAME_H_

struct pos;
class Board;
class GameView;
class Player;

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
    gameState state = ongoing;
    Board* theBoard = nullptr;
    GameView* theView;
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;

public:
    gameState getState();  // get the current state of the board

    void update(pos a, pos b);  // update the board with a move

    // checks to see if a move is valid (only in the sense that it adheres to direction and blocking)
    bool validate(pos a, pos b);  

    char play(); // plays a game, runs game loop

    void setTurn(int colour); // sets curMove to [colour]

    Board* getBoard(); // gets the board

    void setBoard(Board* newBoard);
};  

#endif