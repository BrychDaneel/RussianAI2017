#include "NuclearActiveInterruption.hpp"


#include "AsyncScaleTask.hpp"
#include "SleepTask.hpp"
#include "SpeedBarrierTask.hpp"
#include "SelectTask.hpp"
#include "ChangeActiveTask.hpp"
#include "ChangeStateTask.hpp"


namespace my{

    void NuclearActiveInterruption::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->env = &env;
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }

    void NuclearActiveInterruption::action(){

        if (env->getWorld()->getOpponentPlayer().getNextNuclearStrikeVehicleId() != -1)
                env->setActive(ActiveType::Hight);
        else if (env->getWorld()->getOpponentPlayer().getRemainingActionCooldownTicks() <= env->getGame()->getActionDetectionInterval())
                env->setActive(ActiveType::Low);
        else
                env->setActive(ActiveType::Normal);
    }
}


