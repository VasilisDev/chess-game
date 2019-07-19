//
// Created by vasilis on 13/5/2019.
//

#include "include/King.h"

King::King(Color color) : Piece(color, Type::KING) {

}

/**
 * The king moves one square in any direction.
 * @param board A pointer to a board object.
 * @param from  This is the source piece.
 * @param to    This is the destination piece.
 * @return true if the move is valid otherwise returns false.
 */
bool King::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {

    /* Can move one tile in any direction */
    return board->getMoveLength(from, to) == 1;

}