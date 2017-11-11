#include "GroupingService.hpp"


#include "model/Vehicle.h"
#include <map>
#include "Repos.hpp"
#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "ChangeStateTask.hpp"


namespace my{

    bool GroupingService::action(){
        double cx, cy;
        Repos::getCenter(env->getVehicleManager()->getMy(), cx, cy);

        taskManager->addTask(new ChangeStateTask(StateType::Group));

        taskManager->addTask(new SelectTask("Tanks"));
        taskManager->addTask(new AsyncMoveTask(cx, cy));

        taskManager->addTask(new SelectTask("Arrvs"));
        taskManager->addTask(new AsyncMoveTask(cx, cy));

        taskManager->addTask(new SelectTask("Fighters"));
        taskManager->addTask(new AsyncMoveTask(cx, cy));

        taskManager->addTask(new SelectTask("Helicopters"));
        taskManager->addTask(new AsyncMoveTask(cx, cy));

        taskManager->addTask(new SelectTask("IFVs"));
        taskManager->addTask(new AsyncMoveTask(cx, cy));

        taskManager->addTask(new SpeedBarrierTask(0.1));
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
        this->groupManager = &groupManager;
    }

    GroupingService::~GroupingService(){
    }
}
