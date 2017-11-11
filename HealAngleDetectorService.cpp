#include "HealAngleDetectorService.hpp"


#include "StateType.hpp"
#include "Repos.hpp"
#include <vector>
#include "model/Vehicle.h"


namespace my{

    void HealAngleDetectorService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        vehicleManager = env.getVehicleManager();
    }

    int HealAngleDetectorService::getRate(){
        return RATE;
    }

    bool HealAngleDetectorService::action(){
        if (env->getState() != StateType::Attack)
            return false;

        if (vehicleManager->getmyArrvs().size() == 0){
            env->removeData("AngleX");
            env->removeData("AngleY");
            return false;
        }

        double cx, cy;
        Repos::getCenter(vehicleManager->getMy(), cx, cy);

        double hx, hy;
        Repos::getCenter(vehicleManager->getmyArrvs(), hx, hy);

        angleX = cx - hx;
        angleY = cy - hy;
        env->putData("AngleX", &angleX);
        env->putData("AngleY", &angleY);

        return false;
    }
}
