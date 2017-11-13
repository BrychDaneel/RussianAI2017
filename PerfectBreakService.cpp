#include "PerfectBreakService.hpp"


namespace my{

    void PerfectBreakService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        perfectBreak = env.getMagicConsts().getPerfectBreakPercent();
        vehicleManager = env.getVehicleManager();
        startSize = vehicleManager->getMy().size();
    }

    int PerfectBreakService::getRate(){
        return RATE;
    }

    bool PerfectBreakService::action(){
        if (env->getData("PAngle") == nullptr)
            return false;

        int armySize = vehicleManager->getMy().size() - vehicleManager->getmyArrvs().size();

        if (armySize < perfectBreak * startSize)
            env->removeData("PAngle");

        return false;
    }
}
