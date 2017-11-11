#include "BaseBindService.hpp"


namespace my{
    bool BaseBindService::action(){

        actionManager->select(0, 0, width, height);
        groupManager->bind("All");
        groupManager->bind("Army");

        actionManager->select(0, 0, width, height, model::VehicleType::TANK);
        groupManager->bind("Tanks");

        actionManager->select(0, 0, width, height, model::VehicleType::ARRV);
        groupManager->bind("Arrvs");

        actionManager->select(0, 0, width, height, model::VehicleType::FIGHTER);
        groupManager->bind("Fighters");

        actionManager->select(0, 0, width, height, model::VehicleType::HELICOPTER);
        groupManager->bind("Helicopters");

        actionManager->select(0, 0, width, height, model::VehicleType::IFV);
        groupManager->bind("IFVs");
        return true;
    }

    int BaseBindService::getRate(){
        return RATE;
    }

    void BaseBindService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }
}

