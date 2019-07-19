//
// Created by vasilis on 17/6/2019.
//

#include <string>
#include <utils.h>
#include <algorithm>


/**
 * A function that parses the user input.It converts the algebraic notation to coordinates like an original 2D array.
 * For example a8 a7 is equivalent to 00 10.
 * @param square
 * @return std::pair<int,int>
 */
std::pair<int, int> Utils::parse(std::string square) const {
    //if there is an uppercase letter convert it to lowercase.
    std::transform(square.begin(), square.end(), square.begin(), ::tolower);
    int col = square[0] - 'a';
    int row = 8 - (square[1] - '0');
    return std::make_pair(row, col);
}

/***
 * It makes the revert job from the previous function.It takes numerical coordinate and convert it to algebraic string.
 * @param coords
 * @return std::string
 */
std::string Utils::toAlgebraic(std::pair<int, int> coords) const {
    auto row = static_cast<char>(8 - coords.first + '0');
    auto col = static_cast<char>(coords.second + 'a');
    std::string finalCoords = std::string() + col + row;
    return finalCoords;
}
