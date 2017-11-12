#include "AsyncScaleTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    AsyncScaleTask::AsyncScaleTask(double x, double y, double factor, double maxSpeed){
        scaleType = ScaleType::Point;
        this->x = x;
        this->y = y;
        this->factor = factor;
        this->maxSpeed = maxSpeed;
    }

    AsyncScaleTask::AsyncScaleTask(double factor, double maxSpeed){
        scaleType = ScaleType::Center;
        this->factor = factor;
        this->maxSpeed = maxSpeed;
    }

    void AsyncScaleTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        vehicleManager = env.getVehicleManager();
    }

    bool AsyncScaleTask::action(){
        if (!firtRun)
            return false;
        firtRun = false;

        if (scaleType == ScaleType::Center){
            std::vector<model::Vehicle> selected;
            for (auto pair : vehicleManager->getMy()){
                const model::Vehicle vehicle = pair.second;
                if (vehicle.isSelected())
                    selected.push_back(vehicle);
            }
            double cx, cy;
            Repos::getCenter(selected, cx, cy);
            actionManager->scale(cx, cy, factor, maxSpeed);
        } else
            actionManager->scale(x, y, factor, maxSpeed);

        return true;
    }
}
