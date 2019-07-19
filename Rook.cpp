//
// Created by vasilis on 13/5/2019.
//

#include "include/Rook.h"

Rook::Rook(Color color) : Piece(color,Piece::Type::ROOK) {

}
/**
 *  The rook (or castle) can move any number of squares along any rank or file,
 *  but may not leap over other pieces.
 * @param board
 * @param from
 * @param to
 * @return true if the move is valid otherwise returns false.
 */
bool Rook::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {

    // crosses the rank
    if(board->isRankClear(from,to))
        return true;

    // crosses the file
    return board->isFileClear(from, to);

}








