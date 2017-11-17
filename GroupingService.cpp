#include "GroupingService.hpp"


#include "model/Vehicle.h"
#include <map>
#include "Repos.hpp"
#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "ChangeStateTask.hpp"
#include "GridGroupTask.hpp"


namespace my{

    bool GroupingService::action(){
        double cx, cy;
        Repos::getCenter(env->getVehicleManager()->getMy(), cx, cy);

        taskManager->addTask(new ChangeStateTask(StateType::Group));

        taskManager->addTask(new GridGroupTask(2, 2));

        taskManager->addTask(new SpeedBarrierTask("Army", 0.1));
        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        return true;
    }

    int GroupingService::getRate(){
        return RATE;
    }

    void GroupingService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
    }

    GroupingService::~GroupingService(){
    }
}

