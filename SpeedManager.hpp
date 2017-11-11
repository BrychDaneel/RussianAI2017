#pragma once
#ifndef _MY_SPEED_MANAGER_HPP_
#define _MY_SPEED_MANAGER_HPP_


#include "model/VehicleUpdate.h"
#include "model/Vehicle.h"
#include <vector>
#include <map>


using std::vector;


namespace my{
    class SpeedManager{
        private:
            std::map<long long, double> speed;
            double maxMySpeed;
            size_t len;
        public:
            SpeedManager();
            void update(const std::map<long long,model::Vehicle>& vehicles, int myId, const std::vector<model::VehicleUpdate>& updates);
            double getMaxMySpeed() const;
            double getSpeed(long long id) const;
    };
}


#endif


