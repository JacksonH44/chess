#include "cpu4.h"
#include "../game/game.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../pos.h"
#include <time.h>
#include "../board/board.h"
#include "../board/piece.h"
#include <tuple>

using namespace std;

CPU4::CPU4(int colour, Game* game) : Player{colour}, game{game} {}

Game* CPU4::getGame() {
    return game;
}

tuple<pos, pos, char> CPU4::determineMove(istream& in)
{
    srand(time(NULL));

    Board *theBoard = getGame()->getBoard();

    vector<Piece *> teamPieces = theBoard->getPieces(this->getColour());
    vector<Piece *> availablePieces;
    for (int i = 0; i < teamPieces.size(); ++i)
    {
        if (!((teamPieces[i]->getValidMoves()).empty()))
        {
            availablePieces.emplace_back(teamPieces[i]);
        }
    }

    // filter out moves that put us in check
    vector<tuple<pos, pos>> safeMoves;

    for (int i = 0; i < availablePieces.size(); ++i)
    {
        Piece *curPiece = availablePieces[i];
        pos myPos = curPiece->getPos();
        vector<pos> myMoves = curPiece->getValidMoves();
        for (auto movePos : myMoves)
        {
            Board *snapshot = new Board{*theBoard};
            snapshot->updateBoard(myPos, movePos);
            if (!(snapshot->isChecked(this->getColour())))
            { // this move doesn't put us in check add it to safe moves
                tuple<pos, pos> safeMove{myPos, movePos};
                safeMoves.emplace_back(safeMove);
            }
            delete snapshot;
        }
    }

    // filter out moves that are stalemates, and prioritize any checkmates
    vector<tuple<pos, pos>> stales;
    vector<tuple<pos, pos>> noStales;
    vector<tuple<pos, pos>> checkMates;

    for (auto move : safeMoves) {
        theBoard = getGame()->getBoard();
        Board* snapshot = new Board{*theBoard};
        snapshot->updateBoard(get<0>(move), get<1>(move));
        Game* newGame = new Game();
        newGame->setBoard(snapshot);
        newGame->setTurn((this->getColour() + 1) % 2);
        gameState winState = whiteWin;
        if (this->getColour() == 0) {
            winState = blackWin;
        }
        if (newGame->getState() == winState) 
        { // found a checkmate
            checkMates.emplace_back(move);
        }
        else if (!(snapshot->isChecked((this->getColour() + 1) % 2)) && newGame->getState() == stalemate) 
        { // move makes the game a stalemate
            stales.emplace_back(move);
        } else {
            noStales.emplace_back(move);
        }
        delete newGame;
    }

    // split the no stalemate moves into two groups: one that avoids capture and one that doesn't
    vector<tuple<pos, pos>> cap;
    vector<tuple<pos, pos>> noCap;

    for (auto move : noStales)
    {
        if (theBoard->getPiece(get<1>(move)) != nullptr)
        { // capturing
            cap.emplace_back(move);
        }
        else
        {
            Board *snapshot = new Board{*theBoard};
            snapshot->updateBoard(get<0>(move), get<1>(move));
            if (snapshot->isChecked((this->getColour() + 1) % 2))
            { // puts other player in check
                cap.emplace_back(move);
            }
            else
            {
                noCap.emplace_back(move);
            }
            delete snapshot;
        }
    }

    /**
     * TIER 1: Moves that avoid capture and capture or put the other player in check
     * TIER 2: Moves that capture or put the other player in check but do not avoid capture
     * TIER 3: Moves that avoid capture
     * TIER 4: Random non stalemate moves
     * TIER 5: Stalemate moves
     */
    vector<tuple<pos, pos>> tier1;
    vector<tuple<pos, pos>> tier2;
    vector<tuple<pos, pos>> tier3;
    vector<tuple<pos, pos>> tier4;

    // check to see if any capturing moves avoid capture
    for (auto move : cap)
    {
        bool getsCapped = false;
        Board *snapshot = new Board{*theBoard};
        pos start = get<0>(move);
        pos end = get<1>(move);
        snapshot->updateBoard(start, end);

        // get opponent's pieces
        vector<Piece *> oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
        vector<Piece *> oppAvailablePieces;
        for (int i = 0; i < oppPieces.size(); ++i)
        {
            if (!((oppPieces[i]->getValidMoves()).empty()))
            {
                oppAvailablePieces.emplace_back(oppPieces[i]);
            }
        }

        for (auto oppPiece : oppAvailablePieces)
        {
            for (auto oppMove : oppPiece->getValidMoves())
            {
                if (oppMove == end)
                { // opponent has a move that captures the piece after they've moved
                    tier2.emplace_back(move);
                    getsCapped = true;
                }
            }
        }
        if (!getsCapped)
        {
            tier1.emplace_back(move);
        }
        delete snapshot;
    }

    // check to see if any non capturing moves avoid capture
    for (auto move : noCap)
    {
        bool getsCapped = false;
        Board *snapshot = new Board{*theBoard};
        pos start = get<0>(move);
        pos end = get<1>(move);
        snapshot->updateBoard(start, end);

        // get opponent's pieces
        vector<Piece *> oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
        vector<Piece *> oppAvailablePieces;
        for (int i = 0; i < oppPieces.size(); ++i)
        {
            if (!((oppPieces[i]->getValidMoves()).empty()))
            {
                oppAvailablePieces.emplace_back(oppPieces[i]);
            }
        }

        for (auto oppPiece : oppAvailablePieces)
        {
            for (auto oppMove : oppPiece->getValidMoves())
            {
                if (oppMove == end)
                { // opponent has a move that captures the piece after they've moved
                    tier4.emplace_back(move);
                    getsCapped = true;
                }
            }
        }
        if (!getsCapped)
        {
            tier3.emplace_back(move);
        }
        delete snapshot;
    }

    pos start = {-1, -1};
    pos end = {-1, -1};

    if (!(checkMates.empty())) 
    { // if a checkmate exists
        tuple<pos, pos> selectedMove = checkMates[rand() % checkMates.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    else if (!(tier1.empty()))
    { // if a tier1 move exists
        tuple<pos, pos> selectedMove = tier1[rand() % tier1.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    else if (!(tier2.empty()))
    { // if a tier2 move exists
        tuple<pos, pos> selectedMove = tier2[rand() % tier2.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    else if (!(tier3.empty()))
    { // if a tier3 move exists
        tuple<pos, pos> selectedMove = tier3[rand() % tier3.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }
    else if (!(tier4.empty()))
    { // a tier4 move
        tuple<pos, pos> selectedMove = tier4[rand() % tier4.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    } else 
    { // a stalemate move
        tuple<pos, pos> selectedMove = stales[rand() % stales.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    }

    // pawn promotion
    char newPieceType = ' ';
    if ((theBoard->getPiece(start)->getType() == 'P' && end.y == 0) || (theBoard->getPiece(start)->getType() == 'p' && end.y == 7))
    {
        int pieceChoice = rand() % 4;
        switch (pieceChoice)
        {
        case 0: // Queen
            newPieceType = 'Q';
            break;
        case 1: // Rook
            newPieceType = 'R';
            break;
        case 2: // Bishop
            newPieceType = 'B';
            break;
        default: // Knight
            newPieceType = 'N';
        }
        if (this->getColour() == 0)
        {
            newPieceType += 32; // converts to lowercase if black
        }
    }

    tuple<pos, pos, char> move = {start, end, newPieceType};
    cout << "moving " << theBoard->getPiece(start)->getType() << " from " << convertBack(start) << " to " << convertBack(end) << endl;
    return move;
}