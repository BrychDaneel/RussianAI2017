#include "AttackInterruption.hpp"


#include "Repos.hpp"
#include <cmath>
#include "ChangeStateTask.hpp"
#include "ChangeActiveTask.hpp"
#include "SelectTask.hpp"
#include "AsyncScaleTask.hpp"


#define SQR(X) ((X)*(X))


namespace my{
    void AttackInterruption::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }

    void AttackInterruption::action(){
        if (!first)
            return;
        if (env->getState() != StateType::Group)
            return;
        if (env->getWorld()->getTickIndex() > 3500)
            return;
        if (env->getWorld()->getTickIndex() - lastCall < 30)
            return;
        lastCall = env->getWorld()->getTickIndex();

        double mX, mY;
        Repos::getCenter(env->getVehicleManager()->getMy(), mX, mY);

        double minDist = 10E300;

        for (auto pair : env->getVehicleManager()->getEnemy()){
            model::Vehicle vehicle = pair.second;
            double dist = SQR(vehicle.getX() - mX) + SQR(vehicle.getY() - mY);
            if (minDist > dist)
                minDist = dist;
        }
        minDist = sqrt(minDist);

        if (minDist > env->getMagicConsts().getGroupIntDistance())
            return;

        first = false;

        taskManager->clear();
        actionManager->clear();

        taskManager->addTask(new ChangeStateTask(StateType::Idle));
        taskManager->addTask(new ChangeActiveTask(ActiveType::Normal));
        taskManager->addTask(new SelectTask("Army"));
        taskManager->addTask(new AsyncScaleTask(0.1));
    }
}
