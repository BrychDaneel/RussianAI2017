#include "FrontDetectorService.hpp"


#include "StateType.hpp"
#include "Repos.hpp"
#include "model/Vehicle.h"


namespace my{

    int FrontDetectorService::getRate(){
        return RATE;
    }

    void FrontDetectorService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->damageManager = &env.getDamageManager();
        this->vehicleManager = env.getVehicleManager();
    }

    bool FrontDetectorService::action(){
        if (env->getState()!=StateType::Figth)
            return false;

        double myX, myY;
        Repos::getCenter(vehicleManager->getMy(), myX, myY);
        env->putData("MyX", &myX);
        env->putData("MyY", &myY);

        double damX = 0, damY = 0;
        double damSum = 0;
        std::map<long long, model::Vehicle> all = vehicleManager->getAll();
        for (auto damage : damageManager->getDamageLog())
            for (auto pair : damage)
                if (all.find(pair.first) != all.end()){
                    model::Vehicle vehicle = (*all.find(pair.first)).second;
                    int dam = pair.second;
                    damX += vehicle.getX() * dam;
                    damY += vehicle.getY() * dam;
                    damSum += dam;
                }

        if (damSum < 1)
            return false;

        frontX = damX / damSum;
        frontY = damY / damSum;
        env->putData("FrontX", &frontX);
        env->putData("FrontY", &frontY);

        return false;
    }
}



