#include "SaveService.hpp"


#include "AsyncMoveTask.hpp"
#include "AsyncRotateTask.hpp"
#include "SelectTask.hpp"
#include "StopTask.hpp"
#include "SpeedBarrierTask.hpp"


namespace my{

    void SaveService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        sX = width / 32;
        sY = height / 32;
    }

    int SaveService::getRate(){
        return RATE;
    }

    void SaveService::firstRun(){
        bool has[32][32];
        for (int i=0; i<32; i++)
            for (int ii=0; ii<32; ii++)
             has[i][ii] = false;

        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            has[(int)(vehicle.getX() / sX)][(int)(vehicle.getY() / sY)] = true;
        }

        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new StopTask());
        for (int i=0; i<32; i++)
            for (int ii=0; ii<32; ii++)
                if (has[i][ii]){
                    taskManager->addTask(new SelectTask(i*sX, ii*sY, (i+1)*sX, (ii+1)*sY));
                    taskManager->addTask(new AsyncMoveTask(sX*2, height / 2));
                }
        taskManager->addTask(new SpeedBarrierTask(0.1));
    }

    bool SaveService::action(){
        if (env->getState() != StateType::Save)
            return false;

        if (first)
            firstRun();
        first = false;

        taskManager->addTask(new SelectTask(sX, sY, 10*sX, 31*sY));
        taskManager->addTask(new AsyncRotateTask(width/2, height/2, 3, 0.0, 0.0));

        taskManager->addTask(new SelectTask(22*sX, 0, 31*sX, 31*sY));
        taskManager->addTask(new AsyncRotateTask(width/2, height/2, 3, 0.0, 0.0));

        taskManager->addTask(new SelectTask(sX, sY, 31*sX, 10*sY));
        taskManager->addTask(new AsyncRotateTask(width/2, height/2, 3, 0.0, 0.0));

        taskManager->addTask(new SelectTask(sX, 22*sY, 31*sX, 31*sY));
        taskManager->addTask(new AsyncRotateTask(width/2, height/2, 3, 0.0, 0.0));

        return true;
    }
}



