#include "LoseDetectorService.hpp"


#include "ChangeStateTask.hpp"


namespace my{

    int LoseDetectorService::getRate(){
        return RATE;
    }

    void LoseDetectorService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->vehicleManager = env.getVehicleManager();
        this->taskManager = &taskManager;
        loseCof = env.getMagicConsts().getLoseCof();
    }

    bool LoseDetectorService::action(){
        if (env->getState() == StateType::Save)
            return false;

        int myArmySize = vehicleManager->getMy().size() - vehicleManager->getmyArrvs().size();
        int enemyArmySize = vehicleManager->getEnemy().size() - vehicleManager->getenemyArrvs().size();

        if (myArmySize < loseCof * enemyArmySize){
            taskManager->addTask(new ChangeStateTask(StateType::Save));
            return true;
        }

        return false;
    }
}

