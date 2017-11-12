#include "TempService.hpp"


#include "Repos.hpp"
#include <iostream>


namespace my{

    void TempService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }

    int TempService::getRate(){
        return RATE;
    }

    bool TempService::action(){

        double minX, minY, maxX, maxY;
        Repos::getBox(env->getVehicleManager()->getmyArrvs(), minX, minY, maxX, maxY);
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
        Repos::getBox(env->getVehicleManager()->getmyFighters(), minX, minY, maxX, maxY);
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
        Repos::getBox(env->getVehicleManager()->getmyHelicopters(), minX, minY, maxX, maxY);
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
        Repos::getBox(env->getVehicleManager()->getmyIFVs(), minX, minY, maxX, maxY);
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
        Repos::getBox(env->getVehicleManager()->getmyTanks(), minX, minY, maxX, maxY);
        std::cout << minX << " " << minY << " " << maxX << " " << maxY << std::endl;
        return false;
    }
}


