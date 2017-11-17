#include "FightDetectorService.hpp"


#include "ChangeStateTask.hpp"
#include "StopTask.hpp"
#include "SelectTask.hpp"


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
        if (env->getState() == StateType::Rush || env->getState() == StateType::Save)
            return false;

        bool isFight = damageManager->getSumDamage() >= minFightDamage;
        if (isFight && env->getState() != StateType::Figth){
            taskManager->addTask(new ChangeStateTask(StateType::Figth));
            taskManager->addTask(new SelectTask("Army"));
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


