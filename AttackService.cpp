#include "AttackService.hpp"

#include "AsyncMoveTask.hpp"
#include "StateType.hpp"
#include "ChangeStateTask.hpp"
#include "SelectTask.hpp"


namespace my{

    void AttackService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->taskManager = &taskManager;
        this->env = &env;
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        attackBarrier = env.getMagicConsts().getAttackBorrier();
    }

    int AttackService::getRate(){
        return RATE;
    }

    bool AttackService::action(){
        if (env->getState() != StateType::Idle && env->getState() != StateType::Attack)
            return false;

        if (env->getData("EnemyX") == nullptr || env->getData("EnemyY") == nullptr)
            return false;

        double enemyX = * (double *) env->getData("EnemyX");
        double enemyY = * (double *) env->getData("EnemyY");

        if (enemyX < attackBarrier)
            enemyX = attackBarrier;

        if (enemyX > width - attackBarrier)
            enemyX = width - attackBarrier;

        if (enemyY < attackBarrier)
            enemyY = attackBarrier;

        if (enemyY > height - attackBarrier)
            enemyY = height - attackBarrier;

        double speed = env->getMagicConsts().getDefaultAttackSpeed();
        taskManager->addTask(new ChangeStateTask(StateType::Attack));
        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncMoveTask(enemyX, enemyY, speed));
        return true;

    }

}


