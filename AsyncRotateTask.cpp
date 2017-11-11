#include "AsyncRotateTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    AsyncRotateTask::AsyncRotateTask(double x, double y, double angle, double maxSpeed, double maxAngularSpeed){
        this->x = x;
        this->y = y;
        this->angle = angle;
        this->maxSpeed = maxSpeed;
        this->maxAngularSpeed = maxAngularSpeed;
        rotateType = RotateType::Point;
    }

    AsyncRotateTask::AsyncRotateTask(double angle, double maxSpeed, double maxAngularSpeed){
        this->angle = angle;
        this->maxSpeed = maxSpeed;
        this->maxAngularSpeed = maxAngularSpeed;
        rotateType = RotateType::Center;
    }

    void AsyncRotateTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        vehicleManager = env.getVehicleManager();
    }

    bool AsyncRotateTask::action(){
        if (!firtRun)
            return false;
        firtRun = false;

        if (rotateType == RotateType::Point){
            if (maxAngularSpeed == 0.0)
                actionManager->rotate(x, y, angle, maxSpeed);
            else
                actionManager->rotateAng(x, y, angle, maxAngularSpeed);
            return true;
        }

        std::vector<model::Vehicle> selected;
        for (auto pair : vehicleManager->getMy()){
            const model::Vehicle vehicle = pair.second;
            if (vehicle.isSelected())
                selected.push_back(vehicle);
        }
        double cx, cy;
        Repos::getCenter(selected, cx, cy);

        if (maxAngularSpeed == 0.0)
            actionManager->rotate(cx, cy, angle, maxSpeed);
        else
            actionManager->rotateAng(cx, cy, angle, maxAngularSpeed);

        return true;
    }
}

