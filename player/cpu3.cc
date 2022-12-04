#include "cpu3.h"
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

CPU3::CPU3(int colour, Game* game) : Player{colour}, game{game} {}

Game *CPU3::getGame()
{
    return game;
}

tuple<pos, pos, char> CPU3::determineMove(istream &in)
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

    for (int i = 0; i < availablePieces.size(); ++i) {
        Piece* curPiece = availablePieces[i];
        pos myPos = curPiece->getPos();
        vector<pos> myMoves = curPiece->getValidMoves();
        for (auto movePos : myMoves) {
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

    // split the safe moves into two groups: one that avoids capture and one that doesn't
    vector<tuple<pos, pos>> cap;
    vector<tuple<pos, pos>> noCap;

    for (auto move : safeMoves) {
        if (theBoard->getPiece(get<1>(move)) != nullptr) 
        { // capturing
            cap.emplace_back(move);
        } else 
        { 
            Board* snapshot = new Board{*theBoard};
            snapshot->updateBoard(get<0>(move), get<1>(move));
            if (snapshot->isChecked((this->getColour() + 1) % 2)) 
            { // puts other player in check
                cap.emplace_back(move);
            } else {
                noCap.emplace_back(move);
            }
            delete snapshot;
        }
    }

    /**
     * TIER 1: Moves that avoid capture and capture or put the other player in check
     * TIER 2: Moves that capture or put the other player in check but do not avoid capture
     * TIER 3: Moves that avoid capture
     * TIER 4: Random moves
     */
    vector<tuple<pos, pos>> tier1;
    vector<tuple<pos, pos>> tier2;
    vector<tuple<pos, pos>> tier3;
    vector<tuple<pos, pos>> tier4;

    // check to see if any capturing moves avoid capture
    for (auto move : cap) {
        bool getsCapped = false;
        Board* snapshot = new Board{*theBoard};
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

    // for (auto move : safeMoves) {
    //     bool getsCapped = false;
    //     Board* snapshot = new Board{*theBoard};
    //     pos start = get<0>(move);
    //     pos end = get<1>(move);
    //     snapshot->updateBoard(start, end);

    //     // get opponent's pieces
    //     vector<Piece *> oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
    //     vector<Piece *> oppAvailablePieces;
    //     for (int i = 0; i < oppPieces.size(); ++i)
    //     {
    //         if (!((oppPieces[i]->getValidMoves()).empty()))
    //         {
    //             oppAvailablePieces.emplace_back(oppPieces[i]);
    //         }
    //     }

    //     for (auto oppPiece : oppAvailablePieces) {
    //         for (auto oppMove : oppPiece->getValidMoves()) {
    //             if (oppMove == end) 
    //             { // opponent has a move that captures the piece after they've moved
    //                 getsCap.emplace_back(move);
    //                 getsCapped = true;
    //             }
    //         }
    //     }
    //     if (!getsCapped) {
    //         avoidsCap.emplace_back(move);
    //     }
    //     delete snapshot;
    // }

    

    // // check avoiding capture moves first
    // for (auto move : getsCap) {
    //     if (theBoard->getPiece(get<1>(move)) != nullptr) 
    //     { // other colour piece is there - capturing move
    //         tier1.emplace_back(move);
    //     } else {
    //         Board* snapshot = new Board{*theBoard};
    //         snapshot->updateBoard(get<0>(move), get<1>(move));
    //         if (snapshot->isChecked((this->getColour() + 1) % 2))
    //         { // puts the other player in check
    //             tier1.emplace_back(move);
    //         } else {
    //             tier2.emplace_back(move);
    //         }
    //         delete snapshot;
    //     }
    // }

    // // check non-avoiding capture moves second
    // for (auto move : avoidsCap)
    // {
    //     if (theBoard->getPiece(get<1>(move)) != nullptr)
    //     { // other colour piece is there - capturing move
    //         tier3.emplace_back(move);
    //     }
    //     else
    //     {
    //         Board *snapshot = new Board{*theBoard};
    //         snapshot->updateBoard(get<0>(move), get<1>(move));
    //         if (snapshot->isChecked((this->getColour() + 1) % 2))
    //         { // puts the other player in check
    //             tier3.emplace_back(move);
    //         } else {
    //             tier4.emplace_back(move);
    //         }
    //         delete snapshot;
    //     }
    // }

    // for (int k = 0; k < oppAvailablePieces.size(); ++k)
    // {
    //     Piece *oppSelectedPiece = oppAvailablePieces[k];
    //     vector<pos> curOppValidMoves = oppSelectedPiece->getValidMoves();
    //     for (int l = 0; l < curOppValidMoves.size(); ++l)
    //     {
    //         if (theBoard->getPiece(curOppValidMoves[l]) != nullptr)
    //         { // opponent capturing move
    //             tuple<pos, pos> move{oppSelectedPiece->getPos(), curOppValidMoves[l]};
    //             Board *snapshot = new Board(*theBoard);
    //             snapshot->updateBoard(oppSelectedPiece->getPos(), curOppValidMoves[l]);
    //             if (!(snapshot->isChecked((this->getColour() + 1) % 2)))
    //             { // get the piece that is threatened by the opposition's valid moves
    //                 Piece *myThreatenedPiece = theBoard->getPiece(curOppValidMoves[l]);
    //                 vector<pos> avoidcaptures = myThreatenedPiece->getValidMoves();
    //                 for (int m = 0; m < avoidcaptures.size(); ++m)
    //                 { // add all its moves to the preferred moves
    //                     tuple<pos, pos> myMove{myThreatenedPiece->getPos(), avoidcaptures[m]};
    //                     // make sure move doesn't put us in check
    //                     Board* secondSnapshot = new Board{*theBoard};
    //                     secondSnapshot->updateBoard(myThreatenedPiece->getPos(), avoidcaptures[m]);
    //                     if (!(secondSnapshot->isChecked(this->getColour()))) {
    //                         preferredMoves.emplace_back(myMove);
    //                     }
    //                     delete secondSnapshot;
    //                 }
    //             }
    //             delete snapshot;
    //         }
    //     }
    // }

    // for (int i = 0; i < availablePieces.size(); ++i)
    // {
    //     Piece *selectedPiece = availablePieces[i];
    //     vector<pos> curValidMoves = selectedPiece->getValidMoves();
    //     for (int j = 0; j < curValidMoves.size(); ++j)
    //     {
    //         if (theBoard->getPiece(curValidMoves[j]) != nullptr)
    //         { // capturing move
    //             tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
    //             Board *snapshot = new Board(*theBoard);
    //             snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
    //             if (!snapshot->isChecked(this->getColour()))
    //             {
    //                 preferredMoves.emplace_back(move);
    //             }
    //             delete snapshot;
    //         }
    //         else
    //         {
    //             // look for checkng move
    //             Board *snapshot = new Board(*theBoard);
    //             snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
    //             if (snapshot->isChecked(this->getColour()))
    //             {
    //                 delete snapshot;
    //                 continue; // go next if this move puts us in check
    //             }
    //             pos opKingPos = {-1, -1};
    //             if (this->getColour() == 1)
    //             { // opponent has black king
    //                 opKingPos = snapshot->findPiece('k');
    //             }
    //             else
    //             { // opponent has white king
    //                 opKingPos = snapshot->findPiece('K');
    //             }
    //             tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
    //             if (selectedPiece->isValidMove(opKingPos, snapshot))
    //             { // checking move
    //                 preferredMoves.emplace_back(move);
    //             }
    //             else
    //             {
    //                 safeMoves.emplace_back(move); // non-checking or capturing move but doesn't put us in check
    //             }
    //             delete snapshot;
    //         }
    //     }
    // }

    // pos start = {-1, -1};
    // pos end = {-1, -1};
    // if (!(preferredMoves.empty()))
    // { // if any capturing or checking moves exist, pick a random one
    //     tuple<pos, pos> selectedMove = preferredMoves[rand() % preferredMoves.size()];
    //     start = get<0>(selectedMove);
    //     end = get<1>(selectedMove);
    // }
    // else
    // { // otherwise, pick any move
    //     tuple<pos, pos> selectedMove = safeMoves[rand() % safeMoves.size()];
    //     start = get<0>(selectedMove);
    //     end = get<1>(selectedMove);
    // }
    // // the fact that we aren't in checkmate means there must be at least one available move, so we don't need
    // // to worry about the case where both preferredMoves and safeMoves are empty. If preferredMoves is empty,
    // // then safeMoves must not be

    pos start = {-1, -1};
    pos end = {-1, -1};

    if (!(tier1.empty())) 
    { // if a tier1 move exists
        tuple<pos, pos> selectedMove = tier1[rand() % tier1.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    } else if (!(tier2.empty())) 
    { // if a tier2 move exists
        tuple<pos, pos> selectedMove = tier2[rand() % tier2.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    } else if (!(tier3.empty())) 
    { // if a tier3 move exists
        tuple<pos, pos> selectedMove = tier3[rand() % tier3.size()];
        start = get<0>(selectedMove);
        end = get<1>(selectedMove);
    } else 
    { // a tier4 move
        tuple<pos, pos> selectedMove = tier4[rand() % tier4.size()];
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