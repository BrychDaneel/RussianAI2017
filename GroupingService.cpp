#include "GroupingService.hpp"


#include "model/Vehicle.h"


#include <map>


#include "Repos.hpp"


namespace my{

    bool GroupingService::action(){

        int width = env->getGame()->getWorldWidth();
        int height = env->getGame()->getWorldHeight();

        double goalX, goalY;
        Repos::getCenter(env->getVehicleManager()->getMy(), goalX, goalY);

        double cx, cy;
        actionManager->select(0, 0, width, height, model::VehicleType::VEHICLE_TANK);
        Repos::getCenter(env->getVehicleManager()->getmyTanks(), cx, cy);
        actionManager->move(goalX - cx, goalY - cy);

        actionManager->select(0, 0, width, height, model::VehicleType::VEHICLE_ARRV);
        Repos::getCenter(env->getVehicleManager()->getmyArrvs(), cx, cy);
        actionManager->move(goalX - cx, goalY - cy);

        actionManager->select(0, 0, width, height, model::VehicleType::VEHICLE_FIGHTER);
        Repos::getCenter(env->getVehicleManager()->getmyFighters(), cx, cy);
        actionManager->move(goalX - cx, goalY - cy);

        actionManager->select(0, 0, width, height, model::VehicleType::VEHICLE_HELICOPTER);
        Repos::getCenter(env->getVehicleManager()->getmyHelicopters(), cx, cy);
        actionManager->move(goalX - cx, goalY - cy);

        actionManager->select(0, 0, width, height, model::VehicleType::VEHICLE_IFV);
        Repos::getCenter(env->getVehicleManager()->getmyIFVs(), cx, cy);
        actionManager->move(goalX - cx, goalY - cy);

        for (int i=0; i<300; i++)
            actionManager->nope();

        return true;
    }

    int GroupingService::getRate(){
        return RATE;
    }

    void GroupingService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }

    GroupingService::~GroupingService(){
    }
}
