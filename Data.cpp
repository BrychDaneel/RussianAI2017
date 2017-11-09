#include "Data.hpp"


namespace my{
    Data::~Data(){
        for (auto item : data)
            free(item.second);
    }

    void Data::put(const std::string name, void * const value){
        data[name] = value;
    }

    void* Data::get(const std::string name){
        if (data.find(name) == data.end())
            return nullptr;
        return data[name];
    }

}
