#include "NuclearAttackTask.hpp"


namespace my{
    NuclearAttackTask::NuclearAttackTask(long unitId, double x, double y){
        this->unitId = unitId;
        this->x = x;
        this->y = y;
    }

    void NuclearAttackTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
    }

    bool NuclearAttackTask::action(){
        if (!firstRun)
            return false;
        firstRun = false;

        actionManager->tactical_nuclear_strike(unitId, x, y);

        return true;
    }
}


