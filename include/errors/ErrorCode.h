//
// Created by vasilis on 24/5/2019.
//

#ifndef UNTITLED23_ERRORS_H
#define UNTITLED23_ERRORS_H


namespace Errors {

    enum class ErrorCode {

        SUCCESS ,
        ERROR_GAME_HAS_FINISHED ,
        ERROR_INVALID_INPUT_SOURCE ,
        ERROR_INVALID_INPUT_SOURCE_AND_DESTINATION ,
        ERROR_INVALID_INPUT_DESTINATION ,
        ERROR_NO_PIECE_AT_SOURCE ,
        ERROR_WRONG_PLAYER ,
        ERROR_SOURCE_AND_DESTINATION_SAME ,
        ERROR_FRIENDLY_PIECE_AT_DESTINATION ,
        ERROR_INVALID_PIECE_MOVE ,
        ERROR_OWN_KING_IN_CHECK

    };
}


#endif //UNTITLED23_ERRORS_H
