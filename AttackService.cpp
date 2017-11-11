#include "AttackService.hpp"

#include "AsyncMoveTask.hpp"
#include "StateType.hpp"
#include "ChangeStateTask.hpp"


namespace my{

    void AttackService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->taskManager = &taskManager;
        this->env = &env;
    }

    int AttackService::getRate(){
        return RATE;
    }

    bool AttackService::action(){
        if (env->getState() != StateType::Idle && env->getState() != StateType::Attack)
            return false;

        double *enemyX = (double *) env->getData("EnemyX");
        double *enemyY = (double *) env->getData("EnemyY");
        if (enemyX != nullptr && enemyY != nullptr){
            double speed = env->getMagicConsts().getDefaultAttackSpeed();
            taskManager->addTask(new ChangeStateTask(StateType::Attack));
            taskManager->addTask(new AsyncMoveTask(*enemyX, *enemyY, speed));
            return true;
        }

        return false;
    }

}


