//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_PAWN_H
#define UNTITLED23_PAWN_H

#include "Color.h"
#include <iostream>
#include "Piece.h"
#include "Board.h"

class Pawn : public Piece {

public:
    explicit Pawn(Color color);
    ~Pawn() override = default;
    bool isFirstMove() const;
    void setFirstMove(bool firstMove);
    bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;
    char latin1Representation() const override {
        return _color == Color::WHITE ? 'P' : 'p';
    }

private:
    bool firstMove;


};


#endif //UNTITLED23_PAWN_H
