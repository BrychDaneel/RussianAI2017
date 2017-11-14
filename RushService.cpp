#include "RushService.hpp"

#include "AsyncMoveTask.hpp"
#include "AsyncRotateTask.hpp"
#include "SelectTask.hpp"
#include "StopTask.hpp"
#include "SpeedBarrierTask.hpp"


namespace my{

    void RushService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        sX = width / 32;
        sY = height / 32;
    }

    int RushService::getRate(){
        return RATE;
    }


    bool RushService::action(){
        if (env->getState() != StateType::Rush)
            return false;

        if (env->getData("EnemyX") == nullptr || env->getData("EnemyY") == nullptr)
            return false;

        double enemyX = *(double*)env->getData("EnemyX");
        double enemyY = *(double*)env->getData("EnemyY");

        bool has[32][32];
        for (int i=0; i<32; i++)
            for (int ii=0; ii<32; ii++)
             has[i][ii] = false;

        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            has[(int)(vehicle.getX() / sX)][(int)(vehicle.getY() / sY)] = true;
        }


        for (int i=0; i<32; i++)
            for (int ii=0; ii<32; ii++)
                if (has[i][ii]){
                    taskManager->addTask(new SelectTask(i*sX, ii*sY, (i+1)*sX, (ii+1)*sY));
                    taskManager->addTask(new AsyncMoveTask(enemyX, enemyY));
                }

        return true;
    }
}




