#include "EnemySearchService.hpp"


#include "StateType.hpp"
#include "Repos.hpp"
#include "model/Vehicle.h"


namespace my{

    int EnemySearchService::getRate(){
        return RATE;
    }

    void EnemySearchService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        vehicleManager = env.getVehicleManager();
    }

    bool EnemySearchService::action(){
        if (env->getState() != StateType::Idle && env->getState() != StateType::Attack)
            return false;

        double cx, cy;
        Repos::getCenter(vehicleManager->getMy(), cx, cy);

        long long near = -1;
        double dist;
        for (auto pair : vehicleManager->getEnemy()){
            model::Vehicle vehicle = pair.second;
            if (near == -1){
                near = vehicle.getId();
                dist = vehicle.getDistanceTo(cx, cy);
            } else
                if (dist > vehicle.getDistanceTo(cx, cy)){
                    near = vehicle.getId();
                    dist = vehicle.getDistanceTo(cx, cy);
                }
        }

        if (near!=-1){
            model::Vehicle vehicle = (*vehicleManager->getEnemy().find(near)).second;
            enemyX = vehicle.getX();
            enemyY = vehicle.getY();
            myX = cx;
            myY = cy;
            env->putData("EnemyX", &enemyX);
            env->putData("EnemyY", &enemyY);
            env->putData("MyX", &myX);
            env->putData("MyY", &myY);
        } else{
            env->removeData("EnemyX");
            env->removeData("EnemyY");
        }

        return false;
    }
}



