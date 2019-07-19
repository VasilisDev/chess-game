//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_BOARD_H
#define UNTITLED23_BOARD_H


#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <bitset>
#include "Tile.h"
#include "errors/ErrorCode.h"
#include "Color.h"
#include <optional>


/* Forward declarations */

class Piece;

class Tile;



using namespace std;


class Board final{


public:
    Board();
    void displayBoard();
    Color getTurn();
    string_view printTurn();
    bool isValidCoordinates(const std::pair<int, int> &coords) const;
    bool isEmptyPosition(const std::pair<int, int> &coords) const;
    Piece *getPiece(const std::pair<int, int> &coords) const;
    bool isOccupierPiece(const std::pair<int, int> &to, Color color) const;
    bool isFileClear(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    bool isRankClear(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    bool isDiagonalClear(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    int getMoveLength(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    void submitMove(const std::pair<int, int> &from, const std::pair<int, int> &to);
    bool isVerticalMove(const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const;
    bool isMovingEast(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    bool isMovingSouth(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    bool isHorizontalMove(const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const;
    bool isDiagonalMove(const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const;
    bool isGameIsFinished() const;
    bool isForwardMove(const std::pair<int, int> &fromCoords, const std::pair<int, int> &to, const Piece *piece) const;
    void printMovesHistory()const ;
    void WriteToFileLastTurn(const string &filename);
    void ReadFromFileLastTurn(const string& filename) ;
    ~Board();
    struct InputOutPutHelper {
        char piece;
        int posX;
        int posY;
        bool moved;
    };
    void setGameIsFinished(bool gameIsFinished);
    friend std::ofstream &operator<<(std::ofstream &ofile, Board::InputOutPutHelper const &d);
    void LoadFromFile(string filename);
    InputOutPutHelper io {};



private:
    std::bitset<8> moved[8];
    void changeLastTurn(const string& name);
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> movesHistory;
    std::unique_ptr<Piece> capturedPiece;
    Color colorOfCurrentPlayer;
    std::map<std::pair<int, int>, std::unique_ptr<Tile>> tiles;
    bool gameIsFinished;
    Errors::ErrorCode errorCode;
    std::unique_ptr<Piece> setPiece(const std::pair<int, int> &coords, std::unique_ptr<Piece> piece);
    bool isLegalMove(const std::pair<int, int> &from, const std::pair<int, int> &to);
    void printError(const std::pair<int, int> &from, const std::pair<int, int> &to) const;
    void changeTurn();
    void initTiles();
    void initPawns();
    void initRooks();
    void initKnights();
    void initBishops();
    void initQueens();
    void initKings();
    std::optional<std::pair<int, int>> getLocationOfKing(Color color) const;
    std::vector<std::pair<int, int>> getLocationsByColor(Color color) const;
    std::vector<std::pair<int, int>> getAllLocations() const;
    bool isInCheck(Color defendingColor);
    bool hasAnyValidMove(Color defendingColor);
    void undoLastMove();
    void movePiece(const std::pair<int, int> &from, const std::pair<int, int> &to);
    void SaveToFile(string fileName);
    void updateBoard(const std::pair<int,int> & coords,const char& piece);

};

#endif //UNTITLED23_BOARD_H
