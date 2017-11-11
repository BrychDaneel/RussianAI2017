#include "StopTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    StopTask::StopTask(){
    }

    StopTask::StopTask(int groupId){
        gid = groupId;
    }

    StopTask::StopTask(const std::string& groupName){
        name = groupName;
    }

    void StopTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        vehicleManager = env.getVehicleManager();
    }

    bool StopTask::action(){
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
            actionManager->move(0, 0);
            return true;
        }

        return false;
    }
}

