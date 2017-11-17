#include "FarNuclearService.hpp"


#include "Repos.hpp"
#include <cmath>
#include "NuclearAttackTask.hpp"
#include "StopTask.hpp"
#include "SelectTask.hpp"
#include "ChangeActiveTask.hpp"


#define SQR(X) ((X)*(X))


namespace my{

    void FarNuclearService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->game = env.getGame();
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        this->groupManager = &groupManager;
        this->env = &env;

        farNuclearCount = env.getMagicConsts().getFarNuclearCount();
        minFarRange = env.getMagicConsts().getMinFarRange();
    }

    int FarNuclearService::getRate(){
        return RATE;
    }

    bool FarNuclearService::action(){
        if (env->getState() == StateType::Figth)
            return false;

        if (!env->canNuclear())
            return false;

        int maxCount = -1;
        long maxMyId, maxEnemyX=-1, maxEnemyY=-1;

        std::vector<model::Vehicle> army = groupManager->getVehicles("Army");
        std::vector<model::Vehicle> enemys;
        for (auto pair : vehicleManager->getEnemy())
            enemys.push_back(pair.second);

        double squarMinDist = minFarRange * minFarRange;
        double delta = 2 + env->getMagicConsts().getDefaultAttackSpeed() * env->getGame()->getTacticalNuclearStrikeDelay();

        std::vector<int> neighboards;
        for (size_t i=0; i<enemys.size(); i++){
            neighboards.push_back(0);
            for (size_t ii=0; ii<enemys.size(); ii++)
                if (enemys[i].getSquaredDistanceTo(enemys[ii]) < 2500)
                    neighboards[i]++;
        }

        for (size_t i=0; i<army.size(); i++){
            double squarVision = SQR(env->getTryVisionRange(army[i].getId()) - delta);
            for (size_t ii=0; ii<enemys.size(); ii++){
                double squarDist = army[i].getSquaredDistanceTo(enemys[ii]);
                if ( squarMinDist < squarDist && squarDist < squarVision){

                    if (neighboards[i] > maxCount){
                        maxCount = neighboards[i];
                        maxMyId = army[i].getId();
                        maxEnemyX = enemys[ii].getX();
                        maxEnemyY = enemys[ii].getY();
                    }
                }
            }
        }

        /*for (model::Vehicle vehicle : army)
            for (auto pair : vehicleManager->getEnemy()){
                model::Vehicle enemy = pair.second;
                if (vehicle.getDistanceTo(enemy) >= minFarRange){
                    int count = vehicleManager->getNeighboardCount(enemy.getId(), 50);
                    if (count > maxCount){
                        maxCount = count;
                        maxMyId = vehicle.getId();
                        maxEnemyX = enemy.getX();
                        maxEnemyY = enemy.getY();
                    }
                }
            }*/

        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            double dist = vehicle.getDistanceTo(maxEnemyX, maxEnemyY);
            if (dist < env->getMagicConsts().getNuclearCancelRadius())
                return false;
        }

        model::Vehicle selector = vehicleManager->getMy().find(maxMyId)->second;

        if (maxCount >= farNuclearCount){
            taskManager->addTask(new ChangeActiveTask(ActiveType::Hight));
            taskManager->addTask(new SelectTask("Army", false));
            taskManager->addTask(new StopTask());
            taskManager->addTask(new NuclearAttackTask(maxMyId, maxEnemyX, maxEnemyY));
            taskManager->addTask(new ChangeActiveTask(ActiveType::Normal));
            return true;
        }


        return false;
    }
}
