#include "RushDetectorService.hpp"


#include "ChangeStateTask.hpp"


namespace my{

    int RushDetectorService::getRate(){
        return RATE;
    }

    void RushDetectorService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->vehicleManager = env.getVehicleManager();
        this->taskManager = &taskManager;
        rushCof = env.getMagicConsts().getLoseCof();
        minRushTick = env.getMagicConsts().getMinRushTick();
    }

    bool RushDetectorService::action(){
        if (env->getState() == StateType::Rush)
            return false;

        if (env->getWorld()->getTickIndex() < minRushTick)
            return false;

        int myArmySize = vehicleManager->getMy().size() - vehicleManager->getmyArrvs().size();
        int enemyArmySize = vehicleManager->getEnemy().size() - vehicleManager->getenemyArrvs().size();

        if (myArmySize > rushCof * enemyArmySize){
            taskManager->addTask(new ChangeStateTask(StateType::Rush));
            return true;
        }

        return false;
    }
}

