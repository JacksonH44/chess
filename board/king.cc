#include "king.h"
#include "board.h"
#include <vector>
#include <algorithm>

King::King(int colour, pos position, bool castle) : Piece{colour, &position}, canCastle{canCastle}, type{'k'} {
    if (colour == 1)
    {
        type = 'K';
    }
}

King::King(const King &other) : Piece{other}, type{other.type} {} // copy ctor

King *King::deepCopy() const
{ // deep copy method
    return (new King{*this});
}

bool King::castle(){
    return canCastle;
}

char King::getType() const
{
    return type;
}

void King::updateValidMoves(Board* board, pos p) {
    this->position->x = p.x;
    this->position->y = p.y;

    // move right
    pos tmpPos = pos{this->position->x + 1, this->position->y};
    if (tmpPos.inBounds()) {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour) {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left
    tmpPos = pos{this->position->x - 1, this->position->y};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move down
    tmpPos = pos{this->position->x, this->position->y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move up
    tmpPos = pos{this->position->x, this->position->y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move right down
    tmpPos = pos{this->position->x + 1, this->position->y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move right up
    tmpPos = pos{this->position->x + 1, this->position->y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left down
    tmpPos = pos{this->position->x - 1, this->position->y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left up
    tmpPos = pos{this->position->x - 1, this->position->y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
}

bool King::validate(pos p, Board* board) {
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
