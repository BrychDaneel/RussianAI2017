#include "Repos.hpp"

namespace my{
    void Repos::getCenter(std::vector<model::Vehicle> arr, double & x, double & y){
        int cnt = 0;
        x = 0;
        y = 0;

        for (auto vehicle : arr){
            x += vehicle.getX();
            y += vehicle.getY();
            cnt++;
        }

        x /= cnt;
        y /= cnt;
    }

    void Repos::getCenter(std::map<long long, model::Vehicle> map, double & x, double & y){
        int cnt = 0;
        x = 0;
        y = 0;

        for (auto pair : map){
            model::Vehicle vehicle = pair.second;
            x += vehicle.getX();
            y += vehicle.getY();
            cnt++;
        }

        x /= cnt;
        y /= cnt;
    }

}
