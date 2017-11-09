
#pragma once
#ifndef _MY_INVALID_ANGLE_EXCEPTION_HPP_
#define _MY_INVALID_ANGLE_EXCEPTION_HPP_


#include <exception>


namespace my{
    class InvalidAngleException: public std::exception{
        public:
            InvalidAngleException() : exception(){};
    };
}


#endif
