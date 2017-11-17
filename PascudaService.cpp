#include "PascudaService.hpp"


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


namespace my{

    PascudaService::PascudaService(const bool topPascuda){
        this->topPascuda = topPascuda;
        if (topPascuda)
            pascudaName = "PascudaTop";
        else
            pascudaName = "PascudaRight";
    }

    void PascudaService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        this->groupManager = &groupManager;
        this->env = &env;

        this->nuclearCancelRadius = env.getMagicConsts().getNuclearCancelRadius();
        this->pascudaDelta = env.getMagicConsts().getPascudaDelta();
        this->maxPascudaNuclearDist = env.getMagicConsts().getMaxPascudaNuclearDist();
        this->minPascudaNuclearDist = env.getMagicConsts().getMinPascudaNuclearDist();
        this->maxPascudaDist = env.getMagicConsts().getMaxPascudaDist();
    }

    int PascudaService::getRate(){
        return RATE;
    }

    void PascudaService::firsRun(){
        taskManager->addTask(new SelectTask(pascudaName));
        taskManager->addTask(new AsyncScaleTask(0.1));
        taskManager->addTask(new SpeedBarrierTask(pascudaName, 0.1));


        taskManager->addTask(new SelectTask(pascudaName));
        if (topPascuda)
            taskManager->addTask(new AsyncMoveTask(32 * 5, 1024 - 64));
        else
            taskManager->addTask(new AsyncMoveTask(1024 - 64, 32 * 14));
        taskManager->addTask(new SpeedBarrierTask(pascudaName, 0.1));
    }

    bool PascudaService::action(){
        if (!groupManager->exist(pascudaName))
            return false;

        if (first){
            first = false;
            firsRun();
            return true;
        }

        std::vector<model::Vehicle> vehicles = groupManager->getVehicles(pascudaName);

        if (vehicles.empty())
            return false;


        long long near = -1;
        double dist = 10E100;

        model::Vehicle msp;

        for (model::Vehicle spec : vehicles){

            for (auto pair : vehicleManager->getEnemy()){
                model::Vehicle vehicle = pair.second;
                if (near == -1){
                    near = vehicle.getId();
                    dist = vehicle.getDistanceTo(spec);
                    msp = spec;
                } else
                    if (dist > vehicle.getDistanceTo(spec)){
                        near = vehicle.getId();
                        dist = vehicle.getDistanceTo(spec);
                        msp = spec;
                    }
            }
        }

        if (near==-1)
            return false;

        if (dist < minPascudaNuclearDist){
            taskManager->addTask(new SelectTask(pascudaName));
            if (topPascuda)
                taskManager->addTask(new AsyncDeltaTask(-50, 0));
            else
                taskManager->addTask(new AsyncDeltaTask(0, -50));
            return true;
        }

        model::Vehicle enemy = (*vehicleManager->getEnemy().find(near)).second;
        double enemyX = enemy.getX();
        double enemyY = enemy.getY();

        double enemyVectX = enemyX - msp.getX();
        double enemyVectY = enemyY - msp.getY();

        double nucleX =  enemyX + enemyVectX / dist * (pascudaDelta);
        double nucleY = enemyY + enemyVectY / dist * (pascudaDelta);


        if (msp.getDistanceTo(nucleX, nucleY) > maxPascudaNuclearDist){
            for (model::Vehicle spec1 : vehicles)
                for (model::Vehicle spec2 : vehicles)
                    if (spec1.getDistanceTo(spec2) > maxPascudaDist){
                        taskManager->addTask(new SelectTask(pascudaName));
                        taskManager->addTask(new AsyncScaleTask(0.1));
                        taskManager->addTask(new SpeedBarrierTask(pascudaName, 0.1));
                        return true;
                    }



            double ds = (minPascudaNuclearDist * 0.8 + maxPascudaNuclearDist * 0.2);
            double goalX = enemyX - enemyVectX / dist * ds;
            double goalY = enemyY - enemyVectY / dist * ds;
            taskManager->addTask(new SelectTask(pascudaName));
            taskManager->addTask(new AsyncMoveTask(goalX, goalY));
            return true;
        }

        if (!env->canNuclear())
            return false;


        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            double dist = vehicle.getDistanceTo(nucleX, nucleY);
            if (dist < nuclearCancelRadius)
                return false;
        }

        taskManager->addTask(new SelectTask(pascudaName));
        taskManager->addTask(new StopTask());
        taskManager->addTask(new NuclearAttackTask(msp.getId(), nucleX, nucleY));
        taskManager->addTask(new SleepTask(env->getGame()->getTacticalNuclearStrikeDelay()));
        return true;
    }
}
