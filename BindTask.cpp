#include "BindTask.hpp"



namespace my{

    BindTask::BindTask(const std::string& groupName){
        this->groupName = groupName;
    }

    void BindTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->groupManager = &groupManager;
    }

    bool BindTask::action(){
        if (!firstRun)
            return false;
        firstRun = false;

        groupManager->bind(groupName);
        return true;
    }
}


