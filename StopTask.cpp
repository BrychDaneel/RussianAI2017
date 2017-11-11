#include "StopTask.hpp"


#include <vector>
#include "Repos.hpp"


namespace my{

    StopTask::StopTask(){
    }


    void StopTask::setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager){
        this->actionManager = &actionManager;
    }

    bool StopTask::action(){
        if (!firstRun)
            return false;
        firstRun = false;

        actionManager->move(0, 0);

        return true;
    }
}

