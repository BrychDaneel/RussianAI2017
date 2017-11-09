#include "VehicleManager.hpp"
#include "model/VehicleType.h"


namespace my{

    VehicleManager::VehicleManager(long long myId){
        this->myId = myId;
    }

    void VehicleManager::add(model::Vehicle vehicle){
        for(auto storage : getCategorys(vehicle))
            (*storage)[vehicle.getId()] = vehicle;
    }

    void VehicleManager::update(const model::VehicleUpdate vehicleUpdate){

        long long id = vehicleUpdate.getId();
        model::Vehicle vehicle = vehicleMap[id];

        if (vehicleUpdate.getDurability() == 0){
            for (auto storage : getCategorys(vehicle))
                (*storage).erase(id);
        } else{
            model::Vehicle newVehicle(vehicle, vehicleUpdate);
            for (auto storage : getCategorys(vehicle))
                (*storage)[id] = newVehicle;
        }
    }

    const std::vector<VehicleManager::vehicleStorage*> VehicleManager::getCategorys(const model::Vehicle vehicle){
            std::vector<VehicleManager::vehicleStorage*> result;
            result.push_back(&vehicleMap);
            if (vehicle.getPlayerId() == myId){
                result.push_back(&my);
                switch (vehicle.getType()){
                    case model::VehicleType::VEHICLE_ARRV:
                        result.push_back(&myArrvs);
                        break;
                    case model::VehicleType::VEHICLE_FIGHTER:
                        result.push_back(&myFighters);
                        break;
                    case model::VehicleType::VEHICLE_HELICOPTER:
                        result.push_back(&myHelicopters);
                        break;
                    case model::VehicleType::VEHICLE_IFV:
                        result.push_back(&myIFVs);
                        break;
                    case model::VehicleType::VEHICLE_TANK:
                        result.push_back(&myTanks);
                        break;
                    default:
                        break;
                }
            } else {
                result.push_back(&enemys);
                switch (vehicle.getType()){
                    case model::VehicleType::VEHICLE_ARRV:
                        result.push_back(&enemyArrvs);
                        break;
                    case model::VehicleType::VEHICLE_FIGHTER:
                        result.push_back(&enemyFighters);
                        break;
                    case model::VehicleType::VEHICLE_HELICOPTER:
                        result.push_back(&enemyHelicopters);
                        break;
                    case model::VehicleType::VEHICLE_IFV:
                        result.push_back(&enemyIFVs);
                        break;
                    case model::VehicleType::VEHICLE_TANK:
                        result.push_back(&enemyTanks);
                        break;
                    default:
                        break;
                }
            }
            return result;
    }

    const std::map<long long, model::Vehicle> VehicleManager::getMy() const{
        return my;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getEnemy() const{
        return enemys;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getmyTanks() const{
        return myTanks;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getmyIFVs() const{
        return myIFVs;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getmyHelicopters() const{
        return myHelicopters;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getmyFighters() const{
        return myFighters;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getmyArrvs() const{
        return myArrvs;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getenemyTanks() const{
        return enemyTanks;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getenemyIFVs() const{
        return enemyIFVs;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getenemyHelicopters() const{
        return enemyHelicopters;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getenemyFighters() const{
        return enemyFighters;
    }
    const std::map<long long, model::Vehicle> VehicleManager::getenemyArrvs() const{
        return enemyArrvs;
    }
}
