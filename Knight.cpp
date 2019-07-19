//
// Created by vasilis on 13/5/2019.
//

#include "include/Knight.h"

Knight::Knight(Color color) : Piece(color,Piece::Type::KNIGHT) {

}
/**
 * The knight moves to any of the closest squares that are not on the same rank, file,
 * or diagonal, thus the move forms an ”L”-shape: two squares vertically and one square
 * horizontally, or two squares horizontally and one square vertically. The knight is the
 * only piece that can leap over other pieces.
 * @param board
 * @param from
 * @param to
 * @return true if the move is valid otherwise returns false.
 */
bool Knight::isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const {
    int verticalDifference = abs(to.first - from.first);
    int horizontalDifference = abs(to.second - from.second);

    return (verticalDifference == 2 && horizontalDifference == 1) || (verticalDifference == 1 && horizontalDifference == 2);
}





