#include "CirculStartGroupService.hpp"


#include "model/Vehicle.h"
#include <map>
#include "Repos.hpp"
#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "ChangeStateTask.hpp"
#include "GridGroupTask.hpp"
#include "SleepTask.hpp"
#include "AsyncRotateTask.hpp"
#include "StopTask.hpp"
#include "AsyncScaleTask.hpp"


namespace my{

    bool CirculStartGroupService::action(){
        taskManager->addTask(new ChangeStateTask(StateType::Group));

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncRotateTask(-3, 0.0, 0.0));
        taskManager->addTask(new SleepTask(100));
        taskManager->addTask(new StopTask());

        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SleepTask(100));

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncRotateTask(3, 0.0, 0.0));
        taskManager->addTask(new SleepTask(100));
        taskManager->addTask(new StopTask());

        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SleepTask(100));

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncRotateTask(-3, 0.0, 0.0));
        taskManager->addTask(new SleepTask(100));
        taskManager->addTask(new StopTask());

        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SpeedBarrierTask(0.1));

        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        return true;
    }

    int CirculStartGroupService::getRate(){
        return RATE;
    }

    void CirculStartGroupService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
    }
}
