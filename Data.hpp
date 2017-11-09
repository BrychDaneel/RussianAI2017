#pragma once
#ifndef _MY_DATA_HPP_
#define _MY_DATA_HPP_


#include <string>
#include <map>


namespace my{
    class Data{
        private:
            std::map<const std::string, void *> data;
        public:
            ~Data();
            void put(const std::string name, void * value);
            void* get(const std::string name);
    };
}


#endif
