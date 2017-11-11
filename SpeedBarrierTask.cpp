#include "SpeedBarrierTask.hpp"


namespace my{
    SpeedBarrierTask::SpeedBarrierTask(double maxSpeed){
        this->maxSpeed = maxSpeed;
    }

    void SpeedBarrierTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        speedManager = &env.getSpeedManager();
    }

    bool SpeedBarrierTask::action(){
        if (speedManager->getMaxMySpeed() > maxSpeed)
            return true;
        return false;
    }
}
