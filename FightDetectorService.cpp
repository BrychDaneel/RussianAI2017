#include "FightDetectorService.hpp"


#include "ChangeStateTask.hpp"
#include "StopTask.hpp"


namespace my{

    int FightDetectorService::getRate(){
        return RATE;
    }

    void FightDetectorService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->damageManager = &env.getDamageManager();
        this->taskManager = &taskManager;
        minFightDamage = env.getMagicConsts().getMinFightDamage();
    }

    bool FightDetectorService::action(){
        bool isFight = damageManager->getSumDamage() >= minFightDamage;
        if (isFight && env->getState() != StateType::Figth){
            taskManager->addTask(new ChangeStateTask(StateType::Figth));
            taskManager->addTask(new StopTask());
            return true;
        }

        if (!isFight && env->getState() == StateType::Figth){
            taskManager->addTask(new ChangeStateTask(StateType::Idle));
            return false;
        }
        return false;
    }
}


