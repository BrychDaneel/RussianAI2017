#include "NuclearService.hpp"


#include "Repos.hpp"
#include <cmath>
#include "NuclearAttackTask.hpp"


namespace my{

    void NuclearService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->game = env.getGame();
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        this->groupManager = &groupManager;
        this->env = &env;

        nuclearDist = env.getMagicConsts().getNuclearDist();
        maxNuclearDist = env.getMagicConsts().getMaxNuclearDist();
        minNuclearDistPercent = env.getMagicConsts().getMinNuclearDistPercent();
        maxNuclearDistPercent = env.getMagicConsts().getMaxNuclearDistPercent();
        minVisionCof = env.getMagicConsts().getMinVisionCof();
        nuclearCancelRadius = env.getMagicConsts().getNuclearCancelRadius();
    }

    int NuclearService::getRate(){
        return RATE;
    }

    bool NuclearService::action(){
        if (env->getState() != StateType::Figth)
            return false;

        if (!env->canNuclear())
            return false;

        if (env->getData("FrontX") == nullptr || env->getData("FrontY") == nullptr)
            return false;

        double frontX = *(double*)env->getData("FrontX");
        double frontY = *(double*)env->getData("FrontY");

        double mX, mY;
        std::vector<model::Vehicle> army = groupManager->getVehicles("Army");
        Repos::getCenter(army, mX, mY);

        double nucleX = frontX - mX;
        double nucleY = frontY - mY;
        double d = hypot(nucleX, nucleY);

        if (d > maxNuclearDist)
            return false;

        nucleX = frontX + nucleX / d * nuclearDist;
        nucleY = frontY + nucleY / d * nuclearDist;

        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            double dist = vehicle.getDistanceTo(nucleX, nucleY);
            if (dist < nuclearCancelRadius)
                return false;
        }

        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            double dist = vehicle.getDistanceTo(nucleX, nucleY);
            double vision = vehicle.getVisionRange() * minVisionCof;
            if (vision * minNuclearDistPercent < dist && dist < vision * maxNuclearDistPercent){
                taskManager->addTask(new NuclearAttackTask(vehicle.getId(), nucleX, nucleY));
                return true;
            }
        }

        return false;
    }
}



