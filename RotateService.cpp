#include "RotateService.hpp"


#include "StateType.hpp"
#include "Repos.hpp"
#include <vector>
#include "model/Vehicle.h"
#include <cmath>
#include "AsyncRotateTask.hpp"
#include "ChangeStateTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "SelectTask.hpp"
#include <cmath>

#define SQR(X) ((X)*(X))
#define ABS(X) ((X) > 0 ? (X) : -(X))


#include "SleepTask.hpp"

#include "pi.hpp"


namespace my{

    void RotateService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->taskManager = &taskManager;
        minRotateAngle = env.getMagicConsts().getMinRotateAngle();
        minRotateDistance = env.getMagicConsts().getMinRotateDistance();
        minRotateTime = env.getMagicConsts().getMinRotateTime();
        speedManager = &env.getSpeedManager();
    }

    int RotateService::getRate(){
        return RATE;
    }

    bool RotateService::action(){
        if (env->getState() != StateType::Attack)
            return false;

        if (env->getData("AngleX") == nullptr || env->getData("AngleY") == nullptr ||
            env->getData("EnemyX") == nullptr || env->getData("EnemyY") == nullptr ||
            env->getData("MyX") == nullptr || env->getData("MyY") == nullptr)
            return false;

        double attackX = *(double*)env->getData("EnemyX") - *(double*)env->getData("MyX");
        double attackY = *(double*)env->getData("EnemyY") - *(double*)env->getData("MyY");
        double angleX = *(double*)env->getData("AngleX");
        double angleY = *(double*)env->getData("AngleY");

        bool perfect = false;

        if (env->getData("PAngle") != nullptr){
            perfect = true;
            pAngle = *(double*)env->getData("PAngle");
        }


        double distance = sqrt(SQR(attackX) + SQR(attackY));

        double attackAngle = atan2(attackX, attackY);
        double angle = atan2(angleX, angleY);
        if (perfect)
            angle = pAngle;

        double rot = attackAngle - angle;
        if (rot > PI)
            rot = rot - 2*PI;
        if (rot < -PI)
            rot = 2*PI + rot;

        double enemySpeed = speedManager->getMaxEnemySpeed();
        if (ABS(rot) > minRotateAngle && distance > minRotateDistance && (enemySpeed == 0 || distance / enemySpeed > minRotateTime)){
            taskManager->addTask(new ChangeStateTask(StateType::Group));
            taskManager->addTask(new SelectTask("Army"));
            taskManager->addTask(new AsyncRotateTask(rot, 0.0, 0.0));
            //taskManager->addTask(new SleepTask(1000));
            taskManager->addTask(new SpeedBarrierTask(0.1));
            taskManager->addTask(new ChangeStateTask(StateType::Idle));

            if (perfect){
                pAngle = attackAngle;
                env->putData("PAngle", &pAngle);
            }
            return true;
        }

        return false;
    }
}

