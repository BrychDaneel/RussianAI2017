#include "AsyncMoveTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    AsyncMoveTask::AsyncMoveTask(double x, double y, double maxSpeed){
        this->x = x;
        this->y = y;
        this->maxSpeed = maxSpeed;
    }

    AsyncMoveTask::AsyncMoveTask(int groupId, double x, double y, double maxSpeed){
        gid = groupId;
        this->x = x;
        this->y = y;
        this->maxSpeed = maxSpeed;
    }

    AsyncMoveTask::AsyncMoveTask(const std::string& groupName, double x, double y, double maxSpeed){
        name = groupName;
        this->x = x;
        this->y = y;
        this->maxSpeed = maxSpeed;
    }

    void AsyncMoveTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        vehicleManager = env.getVehicleManager();
    }

    bool AsyncMoveTask::action(){
        taskTick ++;

        if (taskTick == 1 && gid!=0){
            if (name!="")
                groupManager->select(name);
            else
                if (gid == -1)
                    actionManager->select(0, 0, width, height);
                else
                    if (gid)
                        groupManager->select(gid);
            return true;
        }

        if (taskTick == 2 || gid==0){
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

        return false;
    }
}
