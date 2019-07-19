//
// Created by vasilis on 17/6/2019.
//

#ifndef UNTITLED23_UTILS_H
#define UNTITLED23_UTILS_H

#include <string>
#include <sstream>
class Utils{

public:
    Utils() = default;
    ~Utils()= default;
    Utils(const Utils&) = delete;
    Utils(Utils&&) = delete;
    Utils& operator=(const Utils&) = delete;
    Utils& operator=(Utils&&) = delete;

    static Utils& Instance(){
        static Utils util;
        return util;
    }

    std::pair<int, int> parse(std::string square) const;
    std::string toAlgebraic(std::pair<int, int> coords) const ;

};

#endif //UNTITLED23_UTILS_H
