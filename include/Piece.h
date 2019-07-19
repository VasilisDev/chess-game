//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_PIECE_H
#define UNTITLED23_PIECE_H


#include <ostream>
#include "Color.h"
#include "Tile.h"

/* Forward declaration */


using namespace std;

class Board;


class Piece {

public:
    enum class Type {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN,
        NONE
    };
    explicit Piece(Color color,Type type);
    virtual bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const = 0;
    virtual char latin1Representation() const = 0;
    string printColor()const ;
    Color getColor() const;
    Type  getType()  const;
    virtual ~Piece() = default;
    string  printType()const;
    char convertTypeToChar(Type type) const;


protected:
        Color _color;
        Type type;




};


#endif //UNTITLED23_PIECE_H
