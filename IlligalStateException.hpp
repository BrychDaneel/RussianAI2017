#pragma once
#ifndef _MY_ILLIGAL_STATE_EXCEPTION_HPP_
#define _MY_ILLIGAL_STATE_EXCEPTION_HPP_


#include <exception>


namespace my{
    class IlligalStateException: public std::exception{
        public:
            IlligalStateException() : exception(){};
    };
}


#endif
