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

    void Repos::getBox(std::map<long long, model::Vehicle> map, double & minX, double & minY, double & maxX, double & maxY){
        minX = 10e300, maxX = 0, minY = 10e300, maxY = 0;
        for (auto pair : map){
            model::Vehicle vehicle = pair.second;

            if (vehicle.getX() + vehicle.getRadius() > maxX)
                maxX = vehicle.getX() + vehicle.getRadius();

            if (vehicle.getX() - vehicle.getRadius() < minX)
                minX = vehicle.getX() - vehicle.getRadius();

            if (vehicle.getY() + vehicle.getRadius() > maxY)
                maxY = vehicle.getY() + vehicle.getRadius();

            if (vehicle.getY() - vehicle.getRadius() < minY)
                minY = vehicle.getY() - vehicle.getRadius();
        }
    }

    void Repos::getBox(std::vector<model::Vehicle> arr, double & minX, double & minY, double & maxX, double & maxY){
        minX = 10e300, maxX = 0, minY = 10e300, maxY = 0;
        for (auto vehicle : arr){

            if (vehicle.getX() + vehicle.getRadius() > maxX)
                maxX = vehicle.getX() + vehicle.getRadius();

            if (vehicle.getX() - vehicle.getRadius() < minX)
                minX = vehicle.getX() - vehicle.getRadius();

            if (vehicle.getY() + vehicle.getRadius() > maxY)
                maxY = vehicle.getY() + vehicle.getRadius();

            if (vehicle.getY() - vehicle.getRadius() < minY)
                minY = vehicle.getY() - vehicle.getRadius();
        }
    }

}
