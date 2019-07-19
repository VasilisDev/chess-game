//
// Created by vasilis on 13/5/2019.
//

#include "include/Pawn.h"

Pawn::Pawn(Color color) : Piece(color,Piece::Type::PAWN) {

    firstMove = true;
}
/**
 * The pawn may move forward to the unoccupied square immediately in front of it
 * on the same file; or on its first move it may advance two squares along the same file
 * provided both squares are unoccupied; or it may move to a square occupied by an
 * opponent’s piece which is diagonally in front of it on an adjacent file, capturing that piece.
 * @param board
 * @param from
 * @param to
 * @return true if the move is valid otherwise returns false.
 */
bool Pawn::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {

    int rankChange = 0;
    if(_color == Color::WHITE)
        rankChange += 1;
    else
        rankChange -= 1;


    if(!board->isForwardMove(from,to,this)) {
        return false;
    }

    /* If a Pawn moves for first, then it can move two steps vertically */
    if(isFirstMove() && (board->isVerticalMove(from,to) &&(from.first == to.first + rankChange *2))){
        std::pair<int,int> middle = from;
        middle.first -= rankChange;
        if(board->isEmptyPosition(middle) && board->isEmptyPosition(to))
            return true;
    }

    /* Pawn moves one step vertically */
    if(board->isVerticalMove(from,to) && (from.first == to.first + rankChange )) {
        if(board->isEmptyPosition(to))  {
            return true;
        }
    }

    /* Pawn moving diagonally and capturing an enemy piece */
    if(board->isDiagonalMove(from,to) && (from.first == to.first + rankChange )){
        if(board->isOccupierPiece(to, _color))
            return true;
    }
    return false;
}

bool Pawn::isFirstMove() const {
    return firstMove;
}

void Pawn::setFirstMove(bool firstMove) {

    Pawn::firstMove = false;

}


