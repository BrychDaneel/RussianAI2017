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

        /*double minX, minY, maxX, maxY;
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

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncDeltaTask(512, 0));
        taskManager->addTask(new SpeedBarrierTask(0.1));
        taskManager->addTask(new AsyncRotateTask(512,512,3.14,0.0,0.0));
        taskManager->addTask(new SpeedBarrierTask(0.1));
        taskManager->addTask(new AsyncRotateTask(512,512,3.14,0.0,0.0));*/
        taskManager->addTask(new SleepTask(7000));
        return false;
    }
}


