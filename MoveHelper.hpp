#pragma once
#ifndef _MY_MOVE_HELPER_HPP_
#define _MY_MOVE_HELPER_HPP_


#include "model/Move.h"


namespace my{
    class MoveHelper{
        private:
            model::Move* move;
            bool set = false;
            void trySet();
        public:
            MoveHelper(model::Move* move);
            MoveHelper();
            void reset(model::Move* move);
            bool isSet();
            void assign(const model::Move& move);
    };
}


#endif
