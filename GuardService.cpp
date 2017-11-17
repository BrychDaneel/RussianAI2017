#include "GuardService.hpp"


#include "Repos.hpp"
#include "SelectTask.hpp"
#include "AsyncMoveTask.hpp"
#include "AsyncScaleTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "AsyncDeltaTask.hpp"
#include "StopTask.hpp"
#include "NuclearAttackTask.hpp"
#include "SleepTask.hpp"
#include "AsyncScaleTask.hpp"
#include "SleepTask.hpp"
#include "AsyncRotateTask.hpp"


namespace my{


    void GuardService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        this->groupManager = &groupManager;
        this->env = &env;

        guardInteresCount = env.getMagicConsts().getGuardInteresCount();
        guardInteresRadius = env.getMagicConsts().getGuardInteresRadius();
        guardMinArmyDist = env.getMagicConsts().getGuardMinArmyDist();
        guardMaxDist = env.getMagicConsts().getGuardMaxDist();
        guardZoneRadius = env.getMagicConsts().getGuardZoneRadius();
    }

    int GuardService::getRate(){
        return RATE;
    }

    void GuardService::firsRun(){
        taskManager->addTask(new SelectTask(groupName));
        taskManager->addTask(new AsyncRotateTask(3, 0.3, 0.0));
        taskManager->addTask(new SleepTask(30));

        taskManager->addTask(new SelectTask(groupName));
        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SpeedBarrierTask(groupName, 0.1));

        taskManager->addTask(new SelectTask(groupName));
        taskManager->addTask(new AsyncMoveTask(450, 450));
        taskManager->addTask(new SpeedBarrierTask(groupName, 0.1));
    }

    bool GuardService::action(){
        if (!groupManager->exist(groupName))
            return false;

         std::vector<model::Vehicle> guards = groupManager->getVehicles("Guard");

        if (guards.size() == 0)
            return false;

        if (first){
            first = false;
            firsRun();
            return true;
        }

        std::vector<model::Vehicle> army = groupManager->getVehicles("Army");

        double gX, gY;
        Repos::getCenter(guards, gX, gY);

        if (!army.empty())
            for (model::Vehicle vehicle : army)
                if (vehicle.getDistanceTo(gX, gY) < guardMinArmyDist){
                    double vx = vehicle.getX() - gX;
                    double vy = vehicle.getY() - gY;
                    taskManager->addTask(new SelectTask(groupName));
                    taskManager->addTask(new AsyncDeltaTask(-vx, -vy));
                    return true;
                }

        for (model::Vehicle guard1 : guards)
            for (model::Vehicle guard2 : guards)
                if (guard1.getDistanceTo(guard2) > guardMaxDist){
                    taskManager->addTask(new SelectTask(groupName));
                    taskManager->addTask(new AsyncScaleTask(0.1));
                    taskManager->addTask(new SpeedBarrierTask(groupName, 0.1));
                    return true;
                }

        for (auto pair : vehicleManager->getEnemy()){
            model::Vehicle enemy = pair.second;
            if (enemy.getDistanceTo(0, 0) > guardZoneRadius)
                continue;
            if (vehicleManager->getNeighboardCount(enemy.getId(), guardInteresRadius) > guardInteresCount)
                continue;
            taskManager->addTask(new SelectTask(groupName));
            taskManager->addTask(new AsyncMoveTask(enemy.getX(), enemy.getY()));
            return true;
        }

        return false;
    }
}

