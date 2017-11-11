#include "AsyncMoveTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    AsyncMoveTask::AsyncMoveTask(double x, double y, double maxSpeed){
        this->x = x;
        this->y = y;
        this->maxSpeed = maxSpeed;
    }


    void AsyncMoveTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        vehicleManager = env.getVehicleManager();
    }

    bool AsyncMoveTask::action(){
        if (!firtRun)
            return false;
        firtRun = false;

        std::vector<model::Vehicle> selected;
        for (auto pair : vehicleManager->getMy()){
            const model::Vehicle vehicle = pair.second;
            if (vehicle.isSelected())
                selected.push_back(vehicle);
        }
        double cx, cy;
        Repos::getCenter(selected, cx, cy);
        actionManager->move(x - cx, y - cy, maxSpeed);

        return true;
    }
}
