#include "TempService.hpp"


#include "Repos.hpp"
#include "SelectTask.hpp"
#include "SleepTask.hpp"
#include "AsyncRotateTask.hpp"
#include "AsyncDeltaTask.hpp"
#include "SpeedBarrierTask.hpp"
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
        if (!groupManager->exist("Pascuda1") || !groupManager->exist("Pascuda2") || !groupManager->exist("Guard"))
            return false;

        if (firstRun){
            firstRun = false;
            taskManager->addTask(new SelectTask("Pascuda1"));
            taskManager->addTask(new AsyncDeltaTask(0, 500));
            taskManager->addTask(new SelectTask("Pascuda2"));
            taskManager->addTask(new AsyncDeltaTask(0, 400));
            taskManager->addTask(new SelectTask("Guard"));
            taskManager->addTask(new AsyncDeltaTask(0, 300));
            taskManager->addTask(new SpeedBarrierTask("Pascuda1", 0.1));
            return true;
        }

        taskManager->addTask(new SelectTask("Pascuda1"));
        taskManager->addTask(new AsyncDeltaTask(0, sg*100));
        taskManager->addTask(new SleepTask(50));

        sg *= -1;

        return true;
    }
}


