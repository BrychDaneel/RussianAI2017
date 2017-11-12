#pragma once
#ifndef _MY_REPOS_HPP_
#define _MY_REPOS_HPP_


#include "ActionManager.hpp"
#include "model/Vehicle.h"
#include <map>
#include <vector>


namespace my{
    class Repos {
        public:
            static void getCenter(std::vector<model::Vehicle> arr, double & x, double & y);
            static void getCenter(std::map<long long, model::Vehicle> map, double & x, double & y);
            static void getBox(std::vector<model::Vehicle> arr, double & minX, double & minY, double & maxX, double & maxY);
            static void getBox(std::map<long long, model::Vehicle> map, double & minX, double & minY, double & maxX, double & maxY);
    };
}

#endif

