#include "SpeedBarrierTask.hpp"


namespace my{
    SpeedBarrierTask::SpeedBarrierTask(double maxSpeed, bool interrupt){
        this->maxSpeed = maxSpeed;
        this->interrupt = interrupt;
        useGroup = false;
    }

    SpeedBarrierTask::SpeedBarrierTask(const char * groupName, double maxSpeed, bool interrupt){
        this->maxSpeed = maxSpeed;
        this->interrupt = interrupt;
        this->groupName = groupName;
        useGroup = true;
    }

    void SpeedBarrierTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        speedManager = &env.getSpeedManager();
        this->groupManager = &groupManager;
        vehicleManager = env.getVehicleManager();
    }

    bool SpeedBarrierTask::action(){
        if (!useGroup && speedManager->getMaxMySpeed() > maxSpeed)
            return true;

        if (useGroup){
            int gId = groupManager->getId(groupName);

            for (auto pair : vehicleManager->getMy()){
                model::Vehicle vehicle = pair.second;
                for (int unitGroup : vehicle.getGroups())
                    if (unitGroup == gId)
                        if (speedManager->getSpeed(vehicle.getId()) > maxSpeed)
                            return true;
            }
        }

        return false;
    }

    bool SpeedBarrierTask::canInterrupt(){
        return interrupt;
    }

}
