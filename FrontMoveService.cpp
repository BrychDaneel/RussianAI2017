#include "FrontMoveService.hpp"


#include "StateType.hpp"
#include "Repos.hpp"
#include "model/Vehicle.h"
#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"


namespace my{

    int FrontMoveService::getRate(){
        return RATE;
    }

    void FrontMoveService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        moveSpeed = env.getMagicConsts().getFightMoveSpeed();
    }

    bool FrontMoveService::action(){
        if (env->getState()!=StateType::Figth)
            return false;

        if (env->getData("FrontX") == nullptr || env->getData("FrontY") == nullptr)
            return false;

        double frontX = *(double*)env->getData("FrontX");
        double frontY = *(double*)env->getData("FrontY");


        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncMoveTask(frontX, frontY, moveSpeed));

        return true;
    }
}




