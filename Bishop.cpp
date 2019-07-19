//
// Created by vasilis on 13/5/2019.
//

#include "include/Bishop.h"


Bishop::Bishop(Color color) : Piece(color, Piece::Type::BISHOP) {

}
/**
 * The bishop can move any number of squares diagonally, but may not leap over other  pieces
 * @param board
 * @param from
 * @param to
 * @return true if the move is valid otherwise returns false.
 */
bool Bishop::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {


    /* Move along the diagonal */
    return board->isDiagonalClear(from, to);

}




