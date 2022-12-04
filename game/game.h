#ifndef _GAME_H_
#define _GAME_H_

#include <tuple>
#include <vector>

struct pos;
class Board;
class View;
class Player;

enum gameState
{
    whiteWin,
    blackWin,
    whiteChecked,
    blackChecked,
    ongoing,
    tieGame,
    stalemate
};

class Game {
    int curMove;
    gameState state = ongoing;
    Board* theBoard = nullptr;
    std::vector<View*> views;
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;

public:
    ~Game(); // dtor

    gameState getState();  // get the current state of the board

    void notify(pos a, pos b);

    void addView(View* view);

    void clearViews();  // remove all views

    bool isChecked(pos kingPos, int colour);  // Determines whether a player is in check

    void update(pos a, pos b);  // update the board with a move

    // checks to see if a move is valid (only in the sense that it adheres to direction and blocking)
    bool validate(pos a, pos b);  

    char play(); // plays a game, runs game loop

    void setTurn(int colour); // sets curMove to [colour]

    Board* getBoard(); // gets the board

    void setBoard(Board* newBoard);

    bool handlePromotion(pos a, pos b, char piece);

    void handleCastle(pos a, pos b);

    void handlePassant(pos a, pos b);

    bool isBoardValid();
};  

#endif
