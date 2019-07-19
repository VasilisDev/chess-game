//
// Created by vasilis on 13/5/2019.
//

#include "Tile.h"
/**
 * This function firstly hold the right value of {@link#this->piece_} in {@link#std::unique_ptr<Piece> old_piece}.
 * Then put the on {@link#this->piece_} the right hand side value of {@link#std::unique_ptr<Piece> piece}
 * and finally return the {@link#std::unique_ptr<Piece> old_piece} .
 * @param piece The new piece
 * @return  old_piece
 */

std::unique_ptr<Piece> Tile::setPiece(std::unique_ptr<Piece> piece) {
    std::unique_ptr<Piece> old_piece = std::move(this->piece_);
    this->piece_ = std::move(piece);
    return old_piece;
}

/**
 *
 * @return a pointer to a piece object
 */
Piece *Tile::getPiece() const {
    return piece_.get();

}


















