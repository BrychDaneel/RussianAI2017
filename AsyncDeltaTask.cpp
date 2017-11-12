#include "AsyncDeltaTask.hpp"


#include "Repos.hpp"


namespace my{

    AsyncDeltaTask::AsyncDeltaTask(double dx, double dy, double maxSpeed){
        this->dx = dx;
        this->dy = dy;
        this->maxSpeed = maxSpeed;
    }


    void AsyncDeltaTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        vehicleManager = env.getVehicleManager();
    }

    bool AsyncDeltaTask::action(){
        if (!firtRun)
            return false;
        firtRun = false;

        actionManager->move(dx, dy, maxSpeed);

        return true;
    }
}

