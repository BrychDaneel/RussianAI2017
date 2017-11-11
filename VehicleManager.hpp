#pragma once
#ifndef _MY_VEHICLE_MANAGER_HPP_
#define _MY_VEHICLE_MANAGER_HPP_


#include "model/Vehicle.h"
#include "model/VehicleUpdate.h"
#include <map>


namespace my{
    class VehicleManager{

        public:
            using vehicleStorage = std::map<long long, model::Vehicle>;

        private:
            vehicleStorage vehicleMap, my, enemys,
                myTanks, myIFVs, myHelicopters, myFighters, myArrvs,
                enemyTanks, enemyIFVs, enemyHelicopters, enemyFighters, enemyArrvs;
            const std::vector<vehicleStorage*> getCategorys(const model::Vehicle vehicle);
            long long myId;

        public:
            VehicleManager(long long myId);
            void add(const model::Vehicle vehicle);
            void update(const model::VehicleUpdate vehicleUpdate);

            const std::map<long long, model::Vehicle>& getAll() const;
            const std::map<long long, model::Vehicle>& getMy() const;
            const std::map<long long, model::Vehicle>& getEnemy() const;
            const std::map<long long, model::Vehicle>& getmyTanks() const;
            const std::map<long long, model::Vehicle>& getmyIFVs() const;
            const std::map<long long, model::Vehicle>& getmyHelicopters() const;
            const std::map<long long, model::Vehicle>& getmyFighters() const;
            const std::map<long long, model::Vehicle>& getmyArrvs() const;
            const std::map<long long, model::Vehicle>& getenemyTanks() const;
            const std::map<long long, model::Vehicle>& getenemyIFVs() const;
            const std::map<long long, model::Vehicle>& getenemyHelicopters() const;
            const std::map<long long, model::Vehicle>& getenemyFighters() const;
            const std::map<long long, model::Vehicle>& getenemyArrvs() const;
    };
}
#endif

