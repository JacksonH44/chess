#include "queen.h"
#include "board.h"
#include <cstdlib>

Queen::Queen(int colour, pos position): Piece{colour, &position} {}

bool Queen::validate(pos p, Board* board){

    // Check for valid move type for a queen:
    // Check for diagonal move
    int xDist = position->x - p.x;
    int yDist = position->y - p.y;
    if (abs(xDist) != abs(yDist)) { // not diagonal
        // Check for a horizontal move
        if (position->y == p.y) {
            int xStart = position->x;
            int xEnd = p.x;
            if (xDist > 0) {
                xStart = p.x;
                xEnd = position->x;
            }
            for (int i = xStart; i < xEnd; ++i) {
                if (board->getPiece(pos{xStart + i, p.y}) != nullptr)
                {
                    return false;
                }
            }
            return true;  // vertical with no blocking

        } else if (position->x == p.x) { // horizontal move
            int yStart = position->y;
            int yEnd = p.y;
            if (yDist > 0)
            {
                yStart = p.y;
                yEnd = position->y;
            }
            for (int i = yStart; i < yEnd; ++i)
            {
                if (board->getPiece(pos{p.x, yStart + i}) != nullptr)
                {
                    return false;
                }
            }
            return true;  // horizontal with no blocking

        } else {
            return false;  // not diagonal, horizontal, or vertical
        }

        
    } else { // Diagonal, check if there is anything blocking the diagonal
        // right diagonal
        if (xDist * yDist > 0) {
            int xStart = position->x;
            int yStart = position->y;
            if (xStart > p.x) {  // We want to start our checking at the smaller x value 
                xStart = p.x;
                yStart = p.y;
            }
            for (int i = 1; i < xDist; ++i) {
                if (board->getPiece(pos{xStart + i, yStart + i}) != nullptr) {
                    return false;
                }
            }
            return true;  // nothing blocking a right diagonal play
        }
        // left diagonal
        else {
            int xStart = position->x;
            int yStart = position->y;
            if (xStart > p.x) {
                xStart = p.x;
                yStart = p.y;
            }
            for (int i = 1; i < xDist; ++i) {
                if (board->getPiece(pos{xStart + i, yStart - i}) != nullptr)
                {
                    return false;
                }
            }
            return true; // nothing blocking a left diagonal play
        }
    }

    return true;
}

int main() {

    return 0;
}