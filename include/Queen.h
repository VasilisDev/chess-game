//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_QUEEN_H
#define UNTITLED23_QUEEN_H


#include "Piece.h"
#include "Color.h"
#include "Board.h"
#include <iostream>


class Queen : public Piece{

public:
     explicit Queen(Color color);
    ~Queen() override = default;
     bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;
    char latin1Representation() const override {
         return _color == Color::WHITE ?  'Q' :  'q';
    }
};


#endif //UNTITLED23_QUEEN_H
