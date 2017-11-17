#include "DismissTask.hpp"


namespace my{

    DismissTask::DismissTask(const char * groupName){
        this->groupName = groupName;
    }

    void DismissTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->groupManager = &groupManager;
        this->actionManager = &actionManager;
    }

    bool DismissTask::action(){
        if (!firstRun)
            return false;
        firstRun = false;

        actionManager->dismiss(groupManager->getId(groupName));
        return true;
    }
}



