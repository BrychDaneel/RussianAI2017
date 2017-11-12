#include "BaseBindService.hpp"


namespace my{
    bool BaseBindService::action(){

        actionManager->select(0, 0, width, height);
        groupManager->bind("Army");
        return true;
    }

    int BaseBindService::getRate(){
        return RATE;
    }

    void BaseBindService::setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager){
        width = env.getGame()->getWorldWidth();
        height = env.getGame()->getWorldHeight();
        this->actionManager = &actionManager;
        this->groupManager = &groupManager;
    }
}

