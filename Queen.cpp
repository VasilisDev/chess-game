//
// Created by vasilis on 13/5/2019.
//

#include "include/Queen.h"


Queen::Queen(Color color) : Piece(color,Piece::Type::QUEEN) {

}
/**
 * The queen combines the power of the rook and bishop and can move any number of
 * squares along rank, file, or diagonal, but it may not leap over other pieces.
 * @param board
 * @param from
 * @param to
 * @return true if the move is valid otherwise returns false.
 */
bool Queen::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {

    /* crosses the rank */
    if(board->isRankClear(from, to))
        return true;

    /* crosses the file */
    if(board->isFileClear(from, to))
        return true;

    /* crosses the diagonal */
    return board->isDiagonalClear(from, to);
}



