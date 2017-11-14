#include "NuclearService.hpp"


#include "Repos.hpp"
#include <cmath>
#include "NuclearAttackTask.hpp"


namespace my{

    void NuclearService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        this->game = env.getGame();
        this->taskManager = &taskManager;
        this->vehicleManager = env.getVehicleManager();
        this->env = &env;

        nuclearDist = env.getMagicConsts().getNuclearDist();
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

        int cd = game->getBaseTacticalNuclearStrikeCooldown();

        int last = -cd;
        if (env->getData("LastNuclearStrike") != nullptr)
            last = *(int *)env->getData("LastNuclearStrike");

        if (cd > env->getWorld()->getTickIndex() - last)
            return false;

        if (env->getData("FrontX") == nullptr || env->getData("FrontY") == nullptr)
            return false;

        double frontX = *(double*)env->getData("FrontX");
        double frontY = *(double*)env->getData("FrontY");

        double mX, mY;
        Repos::getCenter(vehicleManager->getMy(), mX, mY);

        double nucleX = frontX - mX;
        double nucleY = frontY - mY;
        double d = hypot(nucleX, nucleY);
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
                lastNuclearStrike = env->getWorld()->getTickIndex();
                env->putData("LastNuclearStrike", &lastNuclearStrike);
                return true;
            }
        }

        return false;
    }
}



